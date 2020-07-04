<?php

/*

	File: trending-news-sources.php
	Endpoint: public/trending-news-sources
	Repo: https://github.com/executium/trending-historical-cryptocurrency-news
	License: https://github.com/executium/trending-historical-cryptocurrency-news/LICENSE

*/

include '../src/Executium.trendingnews.Class.php';

$obj = new ExecutiumTrendingNews();

# Parameters required
$payload=array();

# Send Request
$result = $obj->trending_news_sources($payload);

# Result
echo '<pre>';
	echo "\n<strong>Returned</strong>\n\n";
	print_r($result);
echo '</pre>';

?>

