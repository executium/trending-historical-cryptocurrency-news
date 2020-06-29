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
	- [Trending News Statistics](#trending-news-statistics) (public/trending-news-statistics)
- [Contributing](#contributing)

## Introduction

#### Enrichen and enlighten your Algorithms, AI or websites with supplement historical data.
All of the latest cryptocurrency news which is trending today with access to historical data. The API concentrates on providing the following attributes:

- ID
- Title
- Time Created
- Brief
- Source
- Domain
- URL
- Related Keyword(s)
- Keyword Count
- Unique ID
- Image 
- Author

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
* There are currently **`4 endpoints`** for crytocurrency trending news.
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

```php


    
[data] => Array
(
    [0] => Array
	(
		[id] => 3564
		[time_published] => 1593294671
		[title] => Bitcoin Price Bounce at $8.8K Support Shows Traders Keep Buying the Dip
		[keyword] => bitcoin
		[brief] => Bitcoin price dropped below $9000 for the second time this week but traders continue to buy on each dip.
		[url] => https://cointelegraph.com/news/bitcoin-price-bounce-at-88k-support-shows-traders-keep-buying-the-dip
		[source] => Cointelegraph
		[image] => https://s3.cointelegraph.com/storage/uploads/view/a8627213f3baf565b1a1cdb4329867f2.jpg
		[domain] => cointelegraph.com
		[author] => Ray Salmond
	)
)
			
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
      "keywords_monitored":5233,
      "total_articles_found":6756,
      "total_keywords_matched":"6113",
      "sources":741,
      "last_update":1593348146
   },

```

## Contributing

#### Requesting additional keywords to track
If you wish to have more keywords added to the watchlist then please email support@executium.com
