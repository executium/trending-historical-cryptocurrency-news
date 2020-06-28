<?php

/*

	File: trending-news-watchlist.php
	Endpoint: public/trending-news-watchlist
	Repo: https://github.com/executium/trending-historical-cryptocurrency-news
	License: https://github.com/executium/trending-historical-cryptocurrency-news/LICENSE

*/

# Include the executium class
include '../src/Executium.trendingnews.Class.php';

# Declare your key and secret
$obj = new ExecutiumTrendingNews();

# Parameters required
$payload=array();
$payload['keyword_contains']='bitcoin';

# Send Request
$result = $obj->trending_news_watchlist($payload);

# Result
echo '<pre>';
	echo "<strong>Sent</strong>\n\n";
	print_r($payload);
	echo "\n<strong>Returned</strong>\n\n";
	print_r($result);
echo '</pre>';

?>

