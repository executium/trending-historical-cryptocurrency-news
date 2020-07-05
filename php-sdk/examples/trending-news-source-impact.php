<?php

/*

	File: trending-news-source-impact.php
	Endpoint: public/trending-news-source-impact
	Repo: https://github.com/executium/trending-historical-cryptocurrency-news
	License: https://github.com/executium/trending-historical-cryptocurrency-news/LICENSE

*/

# Include the executium class
include '../src/Executium.trendingnews.Class.php';

# Declare your key and secret
$obj = new ExecutiumTrendingNews();

# Parameters required
$payload=array();
$payload['source_contains']='';

# Send Request
$result = $obj->trending_news_source_impact($payload);

# Result
echo '<pre>';
	echo "\n<strong>Returned</strong>\n\n";
	print_r($result);
echo '</pre>';

?>
