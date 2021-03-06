/*
*Author:GeneralSandman
*Code:https://github.com/GeneralSandman/TinyWeb
*E-mail:generalsandman@163.com
*Web:www.generalsandman.cn
*/

/*---XXX---
*
****************************************
*
*/

#include "my_http_parser.h"
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getMessage()
{
    std::cout << "get Message\n";
}

int getUrl()
{
    cout << "get url\n";
}

int getStatus()
{
    cout << "get status\n";
}

int getRequestLine()
{
    cout << "get request line\n";
}

int getHeader()
{
    cout << "get request header\n";
}

int getHeaderKey()
{
    cout << "get header key\n";
}

int getHeaderValue()
{
    cout << "get header value\n";
}

int getBody()
{
    cout << "get body\n";
}

int endMessage()
{
    cout << "end message\n";
}

int getChunk()
{
    cout << "get chunk\n";
}

int endChunk()
{
    cout << "end chunk\n";
}

void testHttpParser()
{
    HttpParserSettings settings;
    settings.setGetMessageCallback(boost::bind(getMessage));
    settings.setGetRequestLineCallback(boost::bind(getRequestLine));
    settings.setGetHeaderCallback(boost::bind(getHeader));
    settings.setGetBodyCallback(boost::bind(getBody));
    settings.setGetEndMessageCallback(boost::bind(endMessage));

    HttpParser parser(&settings);

    parser.invokeByName("getMessage", nullptr, 0);
    parser.invokeByName("getRequestLine", nullptr, 0);
    parser.invokeByName("getHeader", nullptr, 0);
    parser.invokeByName("getBody", nullptr, 0);
    parser.invokeByName("endMessage", nullptr, 0);
}

void testHttpParserResponse()
{

    vector<string> responses = {
        "HTTP/1.1 200 OK\r\n"
        "Date: Tue, 04 Aug 2009 07:59:32 GMT\r\n"
        "Server: Apache\r\n"
        "X-Powered-By: Servlet/2.5 JSP/2.1\r\n"
        "Content-Type: text/xml; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n",

        "HTTP/1.1 304 Not Modified\r\n"
        "Server: Tengine\r\n"
        "Date: Mon, 11 Jun 2018 07:18:14 GMT\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Connection: keep-alive\r\n"
        "Vary: Ali-Detector-Type\r\n"
        "Cache-Control: max-age=60, s-maxage=300\r\n"
        "X-Snapshot-Age: 1\r\n"
        "Content-MD5: DheThrvjUs/c+FtbVv7Sbw==\r\n"
        "ETag: W/\"29d7-163e38938b3\"\r\n"
        "Via: cache9.l2cm12-1[0,304-0,H], cache48.l2cm12-1[0,0], cache6.cn295[0,304-0,H], cache6.cn295[1,0]\r\n"
        "Age: 121\r\n"
        "X-Cache: HIT TCP_IMS_HIT dirn:6:453356086 mlen:-1\r\n"
        "Timing-Allow-Origin: *\r\n"
        "EagleId: 7ceee81815287014946507756e\r\n"
        "Strict-Transport-Security: max-age=31536000\r\n"
        "\r\n",

    };

    HttpParserSettings settings;

    int len = responses.size();
    for (int i = 0; i < len; i++)
    {
        std::cout << "----" << i << std::endl;
        HttpParser parser(&settings);
        parser.setType(HTTP_RESPONSE);
        int begin = 0;
        // parser.execute(responses[i].c_str(), begin, responses[i].size());
    }
}

void testHttpParserRequest()
{

    vector<string> requests = {
        "GET http://127.0.0.1:9999/index.html HTTP/1.1\r\n"
        "Host: 127.0.0.1:9999\r\n"
        "Connection: keep-alive\r\n"
        "\r\n",

        "GET http://127.0.0.1:9999/index.html HTTP/1.1\r\n"
        "Host: www.baidu.com\r\n"
        "Connection: keep-alive\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "Accept: text/html\r\n"
        "Accept-Encoding: gzip, deflate, br\r\n"
        "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "\r\n",

        "GET http://127.0.0.1:9999/index.html HTTP/1.1\r\n"
        "Host: www.dissigil.cn\r\n"
        "Connection: keep-alive\r\n"
        "Pragma: no-cache\r\n"
        "Cache-Control: no-cache\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "Cookie: _ga=GA1.2.2068106829.1526513886; _gid=GA1.2.1899421896.1528880409\r\n"
        "\r\n",

    };

    HttpParserSettings settings;
    // settings.setGetMessageCallback(boost::bind(getMessage));
    // settings.setGetRequestLineCallback(boost::bind(getRequestLine));
    // settings.setGetHeaderCallback(boost::bind(getHeader));
    // settings.setGetBodyCallback(boost::bind(getBody));
    // settings.setGetEndMessageCallback(boost::bind(endMessage));

    int len = requests.size();
    for (int i = 0; i < 1; i++)
    {
        std::cout << i << ")" << std::endl;
        HttpParser parser(&settings);
        parser.setType(HTTP_REQUEST); //FIXME:
        HttpRequest *request = new HttpRequest;
        memset(request, 0, sizeof(HttpRequest));
        parser.execute(requests[i].c_str(), 0, requests[i].size(), request);

        if (request->url != nullptr)
            delete request->url;

        if (request->headers != nullptr)
            delete request->headers;

        if (request->body != nullptr)
            delete request->body;
        delete request;
    }
}

void testParseHeader()
{
    vector<string> strs = {
        "Host: 127.0.0.1:9999\r\n"
        "Connection: keep-alive\r\n"
        "\r\n",

        "Host: 127.0.0.1:9999\r\n"
        "Connection: keep-alive\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
        "Accept-Encoding: gzip, deflate, br\r\n"
        "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "\r\n",

        "sdfasd",

        "Connection: upgrade\r\n"
        ":authority: pingtas.qq.com\r\n"
        ":method: GET\r\n"
        ":path: /webview/pingd?dm=join.qq.com&pvi=3220461568&si=s2709209088&url=/apply.php&arg=&ty=1&rdm=&rurl=&rarg=&adt=&r2=49873873&r3=-1&r4=1&fl=&scr=1366x768&scl=24-bit&lg=zh-cn&jv=&tz=-8&ct=&ext=adid=&pf=&random=1528878932585\r\n"
        ":scheme: https\r\n"
        "\r\n",

        "Accept: text/plain, text/html\r\n"
        "Accept-Charset: iso-8859-5\r\n"
        "Accept-Encoding: compress, gzip\r\n"
        "Accept-Language: en,zh\r\n"
        "Accept-Ranges: bytes\r\n"
        "Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==\r\n"
        "Cache-Control: no-cache\r\n"
        "Connection: close\r\n"
        "Cookie: $Version=1; Skin=new;\r\n"
        "Content-Length: 348\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Date: Tue, 15 Nov&nbsp;2010 08:12:31 GMT\r\n"
        "Expect: 100-continue\r\n"
        "From: user@email.com\r\n"
        "Host: www.zcmhi.com\r\n"
        "\r\n",
    };

    HttpParserSettings settings;

    int len = strs.size();
    for (int i = 0; i < 1; i++)
    {
        HttpParser parser(&settings);
        parser.setType(HTTP_REQUEST);
        std::cout << i << ")\n";

        {
            int return_val = 0;

            char *begin = (char *)strs[i].c_str();
            int offset = 0;
            int str_len = strs[i].size();

            while (1)
            {
                HttpHeader *header = new HttpHeader;
                return_val = parser.parseHeader(begin, offset, str_len, header);
                if (return_val == -1)
                {
                    std::cout << "parse header error\n";
                    break;
                }
                else if (return_val == 0)
                {
                    std::cout << header->keyHash << std::endl;
                    printStr(&(header->key));
                    printStr(&(header->value));
                }
                else if (return_val == 1)
                {
                    std::cout << "parse headers done\n";
                    break;
                }
                std::cout << "index after parseHeader:" << offset << std::endl;

                if (offset == str_len)
                    break;
                offset++;
                delete header;
            }
        }
    }
}

void testParseHeaders()
{
    vector<string> strs = {
        "Host: 127.0.0.1:9999\r\n"
        "Connection: close\r\n"
        "\r\n",

        "Host: 127.0.0.1:9999\r\n"
        "Connection: keep-alive\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
        "Accept-Encoding: gzip, deflate, br\r\n"
        "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "\r\n",

        "Connection: upgrade\r\n"
        ":authority: pingtas.qq.com\r\n"
        ":method: GET\r\n"
        ":path: /webview/pingd?dm=join.qq.com&pvi=3220461568&si=s2709209088&url=/apply.php&arg=&ty=1&rdm=&rurl=&rarg=&adt=&r2=49873873&r3=-1&r4=1&fl=&scr=1366x768&scl=24-bit&lg=zh-cn&jv=&tz=-8&ct=&ext=adid=&pf=&random=1528878932585\r\n"
        ":scheme: https\r\n"
        "\r\n",

        "Connection: close\r\n"
        "Host: 127.0.0.1:9999\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36\r\n"
        "Accept-Encoding: gzip, deflate, br\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "Cookie: _ga=GA1.2.2068106829.1526513886; _gid=GA1.2.1899421896.1528880409\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Content-Length: 1000\r\n"
        "If-Modified-Since: Sat, 29 Oct 2010 19:43:31 GMT\r\n"
        "If-Unmodified-Since: Sat, 29 Oct 2010 19:43:31 GMT\r\n"
        "Last-Modified: Tue, 15 Nov 2010 12:45:26 GMT\r\n"
        "Referer: www.baidu.com\r\n"
        "\r\n",

        "Accept: text/plain, text/html\r\n"
        "Accept-Charset: iso-8859-5\r\n"
        "Accept-Encoding: compress, gzip\r\n"
        "Accept-Language: en,zh\r\n"
        "Accept-Ranges: bytes\r\n"
        "Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==\r\n"
        "Cache-Control: no-cache\r\n"
        "Connection: close\r\n"
        "Cookie: $Version=1; Skin=new;\r\n"
        "Content-Length: 348\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Date: Tue, 15 Nov&nbsp;2010 08:12:31 GMT\r\n"
        "Expect: 100-continue\r\n"
        "From: user@email.com\r\n"
        "Host: www.zcmhi.com\r\n"
        "\r\n",
    };

    HttpParserSettings settings;

    int len = strs.size();
    for (int i = 3; i < 4; i++)
    {
        HttpParser parser(&settings);
        parser.setType(HTTP_REQUEST);
        std::cout << i << ")\n";
        {
            int return_val = 0;

            char *begin = (char *)strs[i].c_str();
            int offset = 0;
            int str_len = strs[i].size();

            HttpHeaders *headers = new HttpHeaders;
            // memset(headers, 0, sizeof(HttpHeaders));
            // headers->generals = std::list<HttpHeader *>();
            headers->host = NULL;
            headers->connection = NULL;
            headers->if_modified_since = NULL;
            headers->if_unmodified_since = NULL;
            headers->user_agent = NULL;
            headers->referer = NULL;

            headers->content_length = NULL;
            headers->content_type = NULL;
            headers->transfer_encoding = NULL;
            headers->accept_encoding = NULL;

            headers->upgrade = NULL;
            headers->expect = NULL;

            headers->cookie = NULL;
            headers->last_modified = NULL;

            headers->content_length_n = 0;
            headers->valid_host = 0;
            headers->valid_referer = 0;

            headers->connection_keep_alive = 0;
            headers->connection_close = 0;

            headers->chrome = 0;

            headers->content_identify_length = 0;
            headers->content_identify_eof = 0;
            headers->chunked = 0;

            return_val = parser.parseHeaders(begin, offset, str_len, headers);
            if (return_val == -1)
            {
                std::cout << "parse headers error\n";
            }
            else if (return_val == 0)
            {
                cout << "header number:" << headers->generals.size() << endl;
                // for (auto t : headers->generals)
                {
                    // std::cout << t->keyHash << std::endl;
                    // printStr(&(t->key));
                    // printStr(&(t->value));
                }
            }

            parser.parseHeadersMeaning(headers);
            printHttpHeaders(headers);

            for (auto t : headers->generals)
                delete t;
            delete headers;
        }
    }
}

void testExecute()
{
    HttpParserSettings settings;
    settings.setGetMessageCallback(boost::bind(getMessage));
    settings.setGetRequestLineCallback(boost::bind(getRequestLine));
    settings.setGetHeaderCallback(boost::bind(getHeader));
    settings.setGetBodyCallback(boost::bind(getBody));
    settings.setGetEndMessageCallback(boost::bind(endMessage));

    HttpParser parser(&settings);
    parser.setType(HTTP_REQUEST);
}

void testHeaderKeyHash()
{
    vector<string> keys =
        {
            "Connection",
            "Content-Length",
            "Host",
            "Content-Type",
            "Accept-Encoding",
            "Cookie",
            "If-Modified-Since",
            "Referer",
            "Last-Modified",
            "Transfer-Encoding",
        };

    for (auto k : keys)
    {
        unsigned long long hash = 0;
        string key;
        for (int i = 0; i < k.size(); i++)
        {
            char ch = k[i];

            if (isLower(ch) || isUpper(ch) || ch == '-')
            {
                ch = toUpper(ch);
                hash = getHash(hash, ch);
            }
            else
            {
                std::cout << "key is invalid\n";
                break;
            }

            key += ch;
            hash = getHash(hash, ch);
        }
        std::cout << key << ":" << hash << std::endl;
        printf("%s:%llu\n", key.c_str(), hash);
    }
}

#include <unordered_map>
void testHeaderKeyHash2()
{
    vector<string> keys =
        {
            "host",
            "connection",
            "if-modified-since",
            "if-unmodified-since",
            "user-agent",
            "referer",

            "content-length",
            "content-type",
            "transfer-encoding",
            "accept-encoding",

            "upgrade",
            "expect",

            "cookie",
            "last-modified",
        };

    vector<string> tests =
        {
            "Host",
            "COnnection",
            "IF-Modified-since",
            "If-unmodified-since",
            "User-agent",
            "Referer",

            "Content-Length",
            "Content-TYpe",
            "Transfer-Encoding",
            "Accept-Encoding",

            "Upgrade",
            "Expect",

            "Cookie",
            "Last-modified",
        };

    extern std::unordered_map<unsigned int, header> headerKeyHash;
    for (auto k : tests)
    {
        unsigned int hash = JSHash(k.c_str(), k.size());
        // std::cout << k << ":" << hash << std::endl;
        auto p = headerKeyHash.find(hash);
        if (p != headerKeyHash.end())
        {
            std::cout << "find" << std::endl;
        }
        else
        {
            std::cout << "not find:" << k << std::endl;
        }
    }
}

typedef struct
{
    char *s1;
    char *s2;
    int len;
} testStr;

void teststrncmp_case()
{
    //TODO:
    // if (0 == strncmp_case("abc\0aaa", "abc\0bbb", 7))
    cout << "same\n";
}

void testGetMethod()
{
    int all = 0;
    int pass = 0;

    for (int i = 0; i < 34; i++)
    {
        const char *method = httpMethodStr((enum http_method)i);
        int len = strlen(method);

        if (i == (unsigned int)getMethod(method, len))
            pass++;
        else
        {
            std::cout << i << ":" << method << std::endl;
        }
        all++;
    }

    std::cout << pass << "/" << all << std::endl;
}

void testLitterCon()
{
    std::string tmp = "[]!@#$%^&*()_++=-:;'<>,./?\"`~";

    std::string str;

    for (int i = 0; i < 26; i++)
    {
        str += char(i + 'a');
        str += char(i + 'A');
    }
    str += tmp;

    std::string up;
    for (int i = 0; i < 26; i++)
    {
        up += char(i + 'A');
        up += char(i + 'A');
    }
    up += tmp;

    std::string lower;
    for (int i = 0; i < 26; i++)
    {
        lower += char(i + 'a');
        lower += char(i + 'a');
    }
    lower += tmp;

    std::string res1;
    for (auto t : str)
        res1 += toLower(t);

    std::string res2;
    for (auto t : str)
        res2 += toUpper(t);

    std::cout << res1 << std::endl
              << lower << std::endl
              << res2 << std::endl
              << up << std::endl;

    if (lower != res1 || up != res2)
        std::cout << "false\n";
    else
    {
        std::cout << "test pass\n";
    }
}

void testAll()
{
    std::string str =
        "GET http://127.0.0.1:9999/index.html HTTP/1.1\r\n"
        "Content-Type: text/xml; charset=utf-8\r\n"
        // "Connection: close\r\n"
        // "Host: 127.0.0.1:9999\r\n"
        // "Accept-Encoding: gzip, deflate, br\r\n"
        // "Upgrade-Insecure-Requests: 1\r\n"
        // "Cookie: _ga=GA1.2.2068106829.1526513886; _gid=GA1.2.1899421896.1528880409\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Content-Length: 16\r\n"
        // "If-Modified-Since: Sat, 29 Oct 2010 19:43:31 GMT\r\n"
        // "If-Unmodified-Since: Sat, 29 Oct 2010 19:43:31 GMT\r\n"
        // "Last-Modified: Tue, 15 Nov 2010 12:45:26 GMT\r\n"
        // "Referer: www.baidu.com\r\n"
        "\r\n"
        //  "<xml>hello</xml>???" /* fake body */;
        "25  \r\n"
        "This is the data in the first chunk..\r\n"
        "1C\r\n"
        "and this is the second one..\r\n"
        "0  \r\n"
        "\r\n";

    HttpParserSettings settings;
    HttpParser parser(&settings);
    parser.setType(HTTP_REQUEST);

    HttpRequest *request = new HttpRequest;
    int return_val = parser.execute(str.c_str(), 0, str.size(), request);

    if (return_val == -1)
        std::cout << "this request is invalid\n";
    else
    {
        std::cout << "request valid[Debug]\n";
        // printUrl(request->url);
        // printHttpHeaders(request->headers);
        // printBody(request->body);
    }
}

// #include <unordered_map>

// void testJSHash()
// {

//     vector<string> keys =
//         {
//             "host",
//             "connection",
//             "if-modified-since",
//             "if-unmodified-since",
//             "user-agent",
//             "referer",

//             "content-length",
//             "content-type",
//             "transfer-encoding",
//             "accept-encoding",

//             "upgrade",
//             "expect",

//             "cookie",
//             "last-modified",
//         };

//     std::unordered_map<unsigned int, string> headerKeyHash;

//     for (auto t : keys)
//     {
//         unsigned int hash = JSHash(t.c_str(), t.size());
//         headerKeyHash[hash] = t;
//     }

//     for (auto t : keys)
//     {
//         unsigned int hash = JSHash(t.c_str(), t.size());
//         if (headerKeyHash[hash] != t)
//             std::cout << "false\n";
//     }
// }

int main()
{
    init();

    // testHttpParser();
    // testHttpParserResponse();
    // testHttpParserRequest();
    // testParseHeader();
    // testParseHeaders();
    // testExecute();
    // testHeaderKeyHash();
    // testHeaderKeyHash2();
    // teststrncmp_case();
    // testGetMethod();
    // testLitterCon();
    testAll();
    // testJSHash();
    return 0;
}
