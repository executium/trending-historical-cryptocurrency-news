<?php

/*

	File: request-trending-news.php
	Endpoint: public/trending-news-data
	Repo: https://github.com/executium/trending-historical-cryptocurrency-news
	License: https://github.com/executium/trending-historical-cryptocurrency-news/LICENSE

*/

# Include the executium class
include '../src/Executium.trendingnews.Class.php';

$obj = new ExecutiumTrendingNews();

# Date Offset
$timestamp=time();
$offset=86400;
$date=date("Y-m-d",$timestamp-$offset);

# Parameters required
$input=array();
$input['date']=$date;
$input['keyword_contains']='';
$input['title_contains']='';
$input['brief_contains']='';
$input['exclude_keywords']='';

# Send Request
$result = $obj->trending_news_data($input);

# Result
echo '<pre>';
	echo "<strong>Sent</strong>\n\n";
	print_r($payload);
	echo "\n<strong>Returned</strong>\n\n";
	print_r($result);
echo '</pre>';

?>
