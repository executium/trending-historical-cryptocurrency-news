<?php

/*

	File: trending-news-statistics.php
	Endpoint: public/trending-news-statistics
	Repo: https://github.com/executium/trending-historical-cryptocurrency-news
	License: https://github.com/executium/trending-historical-cryptocurrency-news/LICENSE

*/

# Include the executium class
include '../src/Executium.trendingnews.Class.php';

# Declare your key and secret
$obj = new ExecutiumTrendingNews();

# Parameters required
$payload=array();

# Send Request
$result = $obj->trending_news_statistics($payload);

# Result
echo '<pre>';
	echo "\n<strong>Returned</strong>\n\n";
	print_r($result);
echo '</pre>';

?>

