# PHP Scripts for Cryptocurrency Trending News
These scripts are provided as examples of how you can pull down data from the executium servers. Please mare sure you have `php-curl` installed for this example to work.

### Examples
The file of most interest to you is likely the `request-trending-news.php`. As follows is a breakdown of how that example file is structured. The endpoint for this example is `https://trendingnews.executium.com/api/v2/public/trending-news-data`

#### Code breakdown
Include the executium trending news class

```php
include '../src/Executium.trendingnews.Class.php';
```
The class
```php
$obj = new ExecutiumTrendingNews();
```

Set the date in `YYYY-MM-DD` format to return an array of that dats data
```php
# Date Offset
$timestamp=time();
$offset=86400;
$date=date("Y-m-d",$timestamp-$offset);
```

Include the parameters for filtering, the `date` parameter is required, without it, the request will fail. 
```php
#Parameters required
$payload=array();
$payload['date']=$date;
$payload['keyword_contains']='';
$payload['title_contains']='';
$payload['brief_contains']='';
$payload['exclude_keywords']='';
```

Send the Request

```php
$result = $obj->trending_news_data($payload);
```

Thats it! You can then manipulate the output of the `$result`.
