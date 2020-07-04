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

Include the parameters for filtering, the `date` parameter is required, without it, the request will fail. These are _POST
```php
# Parameters required (_POST)
$input=array();
$input['date']=$date;
$input['keyword_contains']='';
$input['title_contains']='';
$input['brief_contains']='';
$input['exclude_keywords']='';
```

Send the Request

```php
$result = $obj->trending_news_data($input);
```

Thats it! You can then manipulate the output of the `$result`, for example you can:

**Loop thorugh the data**
```php

foreach($result['data'] as $value)
{
  print_r($value);
}

```

Which will give you an output like

```php

Array
(
    [id] => 779682
    [date] => Array
        (
            [time_published] => 1593822145
            [day] => Saturday
            [format1] => 2020-07-04
            [format2] => 4th July 2020 00:22
        )

    [title] => More South Korean Banks May Look to Start Crypto Operations
    [brief] => More South Korean conventional finance firms are set to follow Nonghyup (NH Bank) into the cryptocurrency industry, say experts, academics and industry ...
    [keywords] => currency,crypto,cryptocurrency
    [url] => https://cryptonews.com/news/more-south-korean-banks-may-look-to-start-crypto-operations-7017.htm
    [source] => Cryptonews
    [image] => https://cimg.co/w/articles/2/5ef/f57c9d47bb.jpg
    [domain] => cryptonews.com
    [author] => Tim Alper
    [price_impact_120s] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

    [price_impact_300s] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

    [price_impact_600s] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

    [price_impact_900s] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

    [price_impact_1200s] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

    [price_impact_1800s] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

    [price_impact_3600s] => Array
        (
            [status] => completed
            [data] => Array
                (
                    [btcusdt] => Array
                        (
                            [status] => compiled
                            [pair] => BTCUSDT
                            [before] => 9060.48000000
                            [after] => 9067.98000000
                            [difference] => 7.50000000
                        )

                    [ethusdt] => Array
                        (
                            [status] => compiled
                            [pair] => ETHUSDT
                            [before] => 225.18000000
                            [after] => 225.40000000
                            [difference] => 0.22000000
                        )

                    [adausdt] => Array
                        (
                            [status] => compiled
                            [pair] => ADAUSDT
                            [before] => 0.09648000
                            [after] => 0.09894000
                            [difference] => 0.00246000
                        )

                    [xrpusdt] => Array
                        (
                            [status] => compiled
                            [pair] => XRPUSDT
                            [before] => 0.17665000
                            [after] => 0.17710000
                            [difference] => 0.00045000
                        )

                    [ethbtc] => Array
                        (
                            [status] => compiled
                            [pair] => ETHBTC
                            [before] => 0.02485400
                            [after] => 0.02485600
                            [difference] => 0.00000200
                        )

                    [adabtc] => Array
                        (
                            [status] => compiled
                            [pair] => ADABTC
                            [before] => 0.00001065
                            [after] => 0.00001091
                            [difference] => 0.00000026
                        )

                    [xrpbtc] => Array
                        (
                            [status] => compiled
                            [pair] => XRPBTC
                            [before] => 0.00001950
                            [after] => 0.00001952
                            [difference] => 0.00000002
                        )

                )

        )

    [tone] => Array
        (
            [status] => Subscription required.
            [data] => Array
                (
                )

        )

)
                        
```

**... or you can simply print_r() the whole array**
```php
print_r($result)
```

