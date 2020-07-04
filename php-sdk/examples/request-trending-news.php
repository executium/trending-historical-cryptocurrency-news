<?php

/*

	File: request-trending-news.php
	Endpoint: public/trending-news-data
	Repo: https://github.com/executium/trending-historical-cryptocurrency-news
	License: https://github.com/executium/trending-historical-cryptocurrency-news/LICENSE

*/

# Include the executium class
include '../src/Executium.trendingnews.Class.php';

# Declare your key and secret
$obj = new ExecutiumTrendingNews();

# Date Offset
$timestamp=time();
$offset=86400;
$date=date("Y-m-d",$timestamp-$offset);

# Parameters required
$payload=array();
$payload['date']=$date;
$payload['keyword_contains']='';
$payload['title_contains']='';
$payload['brief_contains']='';
$payload['exclude_keywords']='';

# Send Request
$result = $obj->trending_news_data($payload);

# Result
echo '<pre>';
	echo "<strong>Sent</strong>\n\n";
	print_r($payload);
	echo "\n<strong>Returned</strong>\n\n";
	print_r($result);
echo '</pre>';

?>
