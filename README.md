# Trending and Historical Cryptocurrency News API
![Trending News](https://i.imgur.com/0SEx35O.jpg)

**Table of Contents**

- [Introduction](#introduction)
- [Authentication](#authentication)
- [Base URL](#base-url)
- [General Information](#general-information)
- [HTTP Return Codes](#http-return-codes)
- [Article Price Impact](#article-price-impact)
- Public
	- [Trending News Data](#trending-news-data) (public/trending-news-data)
	- [Trending News Watchlist](#trending-news-watchlist) (public/trending-news-watchlist)
	- [Trending News Sources](#trending-news-sources) (public/trending-news-sources)
	- [Trending News Source Impact](#trending-news-source-impact) (public/trending-news-source-impact)
	- [Trending News Statistics](#trending-news-statistics) (public/trending-news-statistics)
	- [Trending News Add Keyword](#trending-news-add-keyword) (public/trending-news-add-keyword)
	- [List your own keywords](#list-your-own-keywords) (public/trending-news-list-my-keywords)
	- [Trending News Remove Keyword](#trending-news-remove-keyword) (public/trending-news-remove-keyword)
- [Requesting Keywords](#requesting-keywords)
- [Contributing](#contributing)

## Introduction

#### Enrichen and enlighten your Algorithms, AI or websites with supplement historical data.
All of the latest cryptocurrency news which is trending today with access to historical data. The API concentrates on providing the following attributes:

- ID
- Title
- Date Array
- Brief
- Source
- Domain
- URL
- Related Keyword(s)
- Keyword Count
- Unique ID
- Image 
- Author
- Price Impact

```javacript

{
	"id": "3694",
	"date": 
	{
	  "time_published": "1590754014",
	  "day": "Friday",
	  "format1": "2020-05-29",
	  "format2": "29th May 2020 12:06"
	},
	"title": "Ethereum Significantly Less Private Than Bitcoin, New Research Shows",
	"brief": "Ethereum transactions are even easier to de-anonymize than Bitcoin due to its specifics, but a lot of it comes down to careful usage of mixing tools.",
	"keywords": "bitcoin,Ethereum,eth",
	"url": "https://cointelegraph.com/news/ethereum-significantly-less-private-than-bitcoin-new-research-shows",
	"source": "Cointelegraph",
	"image": "https://s3.cointelegraph.com/storage/uploads/view/c5451bc1be38fbdf6de6f025c637f43d.jpg",
	"domain": "cointelegraph.com",
	"author": "Andrey Shevchenko",
        "price_impact": {
          "status": "Still processing.",
          "data": []
        }	
}	

```

While we provide the related `image` parameter, you *should* always seek permission from the appropriate *copyright* holder for use and publication of any of the data supplied.

#### Watchlist - Keywords
The endpoint `public/trending-news-watchlist` provides the keywords which we currently check the news for.

#### Historical News Scrolling
You can jump through historical news by using the `date` parameter on the `public/trending-news-data`.

## Authentication
You do not need to `authenticate` with any API credentials, but `ratelimits` do apply.

## Base URL
The base URL for using the executium `trending-historical-cryptocurrency-news` is `https://trendingnews.executium.com`

## General Information
* The API is available to the public, rate limits and fair use rules apply.
* The base endpoint is: **`trendingnews.executium.com`**
* All endpoints return a JSON object.
* There are currently **`8 endpoints`** for crytocurrency trending news.
* For `POST` endpoints, the parameters must be sent as a `query string` or in the `request body`.
* For `GET` endpoints, parameters must be sent as a `query string`.
* Parameters may be sent in any order.
* If a parameter sent in both the `query string` and `request body`, the `query string` parameter will take priority.

## HTTP Return Codes

* HTTP `4XX` return codes are used for malformed requests where the issue exists with the sender.
* HTTP `422` return code is applied when a user input is unexpected.
* HTTP `429` return code is used when breaking a request rate limit.
* HTTP `418` return code is used when an IP has been banned automatically for continuing to send requests after receiving `429` codes.
* HTTP `5XX` return codes are used for internal errors where the issue is with the executium side.

## Article Price Impact
Within each article you will find the array `price_impact`. This array provides the following data points:

- A aggregated price capture 300 seconds before an article was published
- A aggregated price capture 3600 seconds after the article was published
- A difference of after minus before (after-before)

Currently we capture the following pairs:

- BTCUSDT
- ETHUSDT
- ADAUSDT
- XRPUSDT
- ETHBTC
- ADABTC
- XRPBTC

## Trending News Data
Trending news data is display on a day per day basis. The date format must be YYYY-MM-DD. You have the additional option to utilize `keyword_contains` which will enable you to pull back all data on keywords which contain your string. This ability is also extended with `title_contains` and `brief_contains`. For multiple keywords to search add a coma (,) onto the string and the system will search for multiple, up to a maximum of 10 per contains.

```
POST /api/v2/public/trending-news-data
```

**Parameters:**
Name | MinLength | Required | Default | Description
------------ | ------------ | ------------ | ------------ | ------------
date | 9 | YES |  | Format YYYY-MM-DD
keyword_contains |  | NO |  | Search for a particular keyword in the `keyword`
title_contains |  | NO |  | Search for a particular keyword in the `title`
brief_contains |  | NO |  | Search for a particular keyword in the `brief`

```javascript

"data": [
      {
        "id": "3694",
        "date": {
          "time_published": "1590754014",
          "day": "Friday",
          "format1": "2020-05-29",
          "format2": "29th May 2020 12:06"
        },
        "title": "Ethereum Significantly Less Private Than Bitcoin, New Research Shows",
        "brief": "Ethereum transactions are even easier to de-anonymize than Bitcoin due to its specifics, but a lot of it comes down to careful usage of mixing tools.",
        "keywords": "bitcoin,Ethereum,eth",
        "url": "https://cointelegraph.com/news/ethereum-significantly-less-private-than-bitcoin-new-research-shows",
        "source": "Cointelegraph",
        "image": "https://s3.cointelegraph.com/storage/uploads/view/c5451bc1be38fbdf6de6f025c637f43d.jpg",
        "domain": "cointelegraph.com",
        "author": "Andrey Shevchenko",
        "price_impact": {
          "status": "3 pending",
          "data": {
            "btcusdt": {
              "status": "compiled",
              "pair": "BTCUSDT",
              "before": "9382.55000000",
              "after": "9415.99000000",
              "difference": "33.44000000"
            },
            "ethusdt": {
              "status": "compiled",
              "pair": "ETHUSDT",
              "before": "218.47000000",
              "after": "219.82000000",
              "difference": "1.35000000"
            },
            "adausdt": {
              "status": "compiled",
              "pair": "ADAUSDT",
              "before": "0.06299000",
              "after": "0.06387000",
              "difference": "0.00088000"
            },
            "xrpusdt": {
              "status": "compiled",
              "pair": "XRPUSDT",
              "before": "0.19750000",
              "after": "0.19758000",
              "difference": "0.00008000"
            },
            "ethbtc": {
              "status": "pending",
              "pair": "ETHBTC"
            },
            "adabtc": {
              "status": "pending",
              "pair": "ADABTC"
            },
            "xrpbtc": {
              "status": "pending",
              "pair": "XRPBTC"
            }
          }
        }
      },
      
      ...
      ...
]

```

## Trending News Watchlist
This endpoint provides you will the full list of keywords which our trending news topic tracker looks against. 

```
POST /api/v2/public/trending-news-watchlist
```

**Parameters:**
Name | MinLength | Required | Default | Description
------------ | ------------ | ------------ | ------------ | ------------
keyword_contains |  | NO |  | Search for a particular keyword in the keyword


**Successful Response Payload:**
```javascript
 {
    "data": [
      {
        "id": "1",
        "keywords": "btc/usdt",
        "recategory": "btcusdt",
        "article_count": "0"
      },
      {
        "id": "2",
        "keywords": "btcusdt",
        "recategory": "btcusdt",
        "article_count": "0"
      },
      {
        "id": "3",
        "keywords": "bitcoin",
        "recategory": "btcusdt",
        "article_count": "0"
      },
      {
        "id": "4",
        "keywords": "true coin",
        "recategory": "btcusdt",
        "article_count": "0"
      },
      {
        "id": "5",
        "keywords": "ETH/BTC",
        "recategory": "ethbtc",
        "article_count": "0"
      },
}
]
```


## Trending News Sources
A list of all the news sources which have featured in the trending news catalog. Review `public/trending-news-statistics` for more statistics and whole number counts.

```
GET /api/v2/public/trending-news-sources
```

**Parameters:**
None

**Successful Response Payload:**
```javascript
 {
    "data": [
      "3rd Watch News",
      "9to5Mac",
      "About Manchester",
      "Actu Crypto.info",
      "AiThority",
      "allnews.ch",
      "alloaadvertiser.com",
      "Altcoin Buzz",
      "AMBCrypto",
      "AMBCrypto English",
      "AMEinfo",
}
```
## Trending News Source Impact
A complete compiled list to provide insight into news sources impact on prices. You can filter the `source` by using `source_contains`, which will allow you to concentrate on specific sources you want. The `top_ranking_*` array contains the all time list of articles that we have stored and their individual impact.  The `most_recent_*` array provides the most reason `bull` and `bear` articles from the publication.
	
It is important to note, that while some publications seem to have a big impact on price, we are not indicating that they we`re the sole reason for the movement. The intention of this endpoint is to provide additional context to whether the press directly impacts prices or if it is just a fluke.


```
POST /api/v2/public/trending-news-source-impact
```

**Parameters:**
Name | MinLength | Required | Default | Description
------------ | ------------ | ------------ | ------------ | ------------
source_contains |  | NO |  | Search for a particular keyword in the `source`


**Successful Response Payload:**
```javascript


"data":
{
	"btcusdt":
	{
		"Cryptonaute":
		{
            "total_articles":410,
            "sum_impact":"590.12000000",
            "top_ranking_bull":[
               {
                  "id":"3836",
                  "keywords":"bitcoin,Ethereum,eth",
                  "time_published":"1587020400",
                  "diff_btcusdt":"233.50000000",
                  "ago":"11 weeks ago"
               },
               {
                  "id":"4011",
                  "keywords":"bitcoin",
                  "time_published":"1592204400",
                  "diff_btcusdt":"90.70000000",
                  "ago":"2 weeks ago"
               },
               {
                  "id":"3831",
                  "keywords":"Ethereum,eth",
                  "time_published":"1589439600",
                  "diff_btcusdt":"63.54000000",
                  "ago":"7 weeks ago"
               },
               {
                  "id":"3777",
                  "keywords":"Ethereum,eth",
                  "time_published":"1592377200",
                  "diff_btcusdt":"37.10000000",
                  "ago":"2 weeks ago"
               },
               {
                  "id":"3839",
                  "keywords":"Ethereum,eth",
                  "time_published":"1589204706",
                  "diff_btcusdt":"34.54000000",
                  "ago":"7 weeks ago"
               }
            ],
            "top_ranking_bear":[
               {
                  "id":"3810",
                  "keywords":"Ethereum,eth",
                  "time_published":"1589918155",
                  "impact":"-16.50000000",
                  "ago":"6 weeks ago"
               }
            ],
            "most_recent_bull":[
               {
                  "id":"4001",
                  "keywords":"bitcoin",
                  "time_published":"1593172260",
                  "diff_btcusdt":"26.14000000",
                  "ago":"3 days ago"
               },
               {
                  "id":"3768",
                  "keywords":"bitcoin,Ethereum,eth",
                  "time_published":"1592910300",
                  "diff_btcusdt":"31.23000000",
                  "ago":"6 days ago"
               },
               {
                  "id":"3773",
                  "keywords":"Ethereum,eth",
                  "time_published":"1592812980",
                  "diff_btcusdt":"10.43000000",
                  "ago":"1 weeks ago"
               },
               {
                  "id":"3792",
                  "keywords":"Ethereum,eth",
                  "time_published":"1592496660",
                  "diff_btcusdt":"2.76000000",
                  "ago":"2 weeks ago"
               },
               {
                  "id":"3777",
                  "keywords":"Ethereum,eth",
                  "time_published":"1592377200",
                  "diff_btcusdt":"37.10000000",
                  "ago":"2 weeks ago"
               }
            ],
            "most_recent_bear":[
               {
                  "id":"3810",
                  "keywords":"Ethereum,eth",
                  "time_published":"1589918155",
                  "impact":"-16.50000000",
                  "ago":"6 weeks ago"
               }
            ]
         },
     },
 }
         	
	
```

## Trending News Statistics
Statistics relating to the trending news catalog. The parameter `total_keywords_matched` can be much higher than total_articles_found as 100s of keywords can be matched to a single article.

```
GET /api/v2/public/trending-news-statistics
```

**Parameters:**
None

**Successful Response Payload:**
```javascript

 "data": 
 {
      "keywords_monitored": 5235,
      "total_articles_found": 13100,
      "total_keywords_matched": 11372,
      "history": [
        {
          "added_in_last_hour": 570
        },
        {
          "last_24_hours": 454
        },
        {
          "last_48_hours": 725
        },
        {
          "last_7_days": 2265
        },
        {
          "last_30_days": 4927
        }
      ],
      "sources": 1406,
      "last_update": 1593408099
	}

```


## Trending News Add Keyword


```
POST /api/v2/public/trending-news-add-keyword
```

**Parameters:**
Name | MinLength | Required | Default | Description
------------ | ------------ | ------------ | ------------ | ------------
name | 1 | YES |  | The `keyword` you want to track.


**Successful Response Payload:**
```javascript
"data": {
      "code": 2001,
      "error": "Missing Key"
    },
```


## List your own keywords


```
POST /api/v2/public/trending-news-list-my-keywords
```

**Parameters:**
Name | MinLength | Required | Default | Description
------------ | ------------ | ------------ | ------------ | ------------
limit |  | NO | 10 | 
page |  | NO | 1 | 


**Successful Response Payload:**
```javascript
"data": {
      "code": 2001,
      "error": "Missing Key"
    },
```


## Trending News Remove Keyword


```
POST /api/v2/public/trending-news-remove-keyword
```

**Parameters:**
Name | MinLength | Required | Default | Description
------------ | ------------ | ------------ | ------------ | ------------
keywordid |  | YES |  | The `keyword_id` you wish to remove. You can get this information from the `public/trending-news-list-my-keywords` endpoint.


**Successful Response Payload:**
```javascript
"data": {
      "code": 2001,
      "error": "Missing Key"
    },
```

## Requesting Keywords
If you wish to track your own list of keywords, we have subscription models for that.
