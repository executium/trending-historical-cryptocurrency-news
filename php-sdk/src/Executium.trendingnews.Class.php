<?php

	class ExecutiumTrendingNews
	{

		public $version=2;
		public $domain='https://trendingnews.executium.com';
		public $useragent='executium TrendingNews API v2';
		public $path='';
		public $url='';
		public $endpoints=array();
		public $timeout=3000;

		public function config($arr)
		{
			foreach($arr as $i=>$v)
			{
				$this->$i = $v;
			}
		}

		public function get_api_url($path)
		{
			return $this->domain . '/api/v' . $this->version . '/' . $path;
		}

		public function set_path($path)
		{
			$this->path = $path;
		}

		public function get_config()
		{
			return $this;
		}

		public function send($path,$input,$payload)
		{
			$this->set_path($path);
			return $this->post($input,$payload);
		}

		public function post($input,$payload)
		{
			$ch = curl_init();

			##/
			if(!$ch)
			{
				return (object)array('code'=>100,'error'=>'PHP-CURL not enabled');
			}
			else
			{
				//
				$this->payload=$payload;
				//
				$this->url = $this->domain . '/api/v' . $this->version . '/' . $this->path;

				//
				curl_setopt($ch, CURLOPT_URL,            $this->url);
				curl_setopt($ch, CURLOPT_HEADER,         false);
				curl_setopt($ch, CURLOPT_RETURNTRANSFER, false);
				curl_setopt($ch, CURLOPT_NOPROGRESS,     true);
				curl_setopt($ch, CURLOPT_TIMEOUT_MS,     $this->timeout);
				curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
				curl_setopt($ch, CURLOPT_USERAGENT,     $this->useragent);

				##/
				if(count($input)>0)
				{
					##/
					curl_setopt($ch,CURLOPT_POST, count($input));
					curl_setopt($ch,CURLOPT_POSTFIELDS, http_build_query($input));
				}

				##/
				ob_start();curl_exec($ch); $return = ob_get_clean(); $out=array('success'=>false,'returned'=>array(),'network_info'=>array());

				##/
				if(empty($return))
				{
					##/
					$out['success']=false;
					$out['returned']=$return;
					$out['network_info']=$return=curl_getinfo($ch);
				}
				else
				{
					$out['success']=true;
					$out['returned'] = json_decode(trim($return),JSON_FORCE_OBJECT);
					$out['network_info']=$return=curl_getinfo($ch);
				}

				curl_close($ch);
			}

			return $out;
		}

		public function trending_news_data($input)
		{
			$this->set_path('public/trending-news-data');
			return $this->post($input,array());
		}

		public function trending_news_sources($input)
		{
			$this->set_path('public/trending-news-sources');
			return $this->post($input,array());
		}

		public function trending_news_source_impact($input)
		{
			$this->set_path('public/trending-news-source-impact');
			return $this->post($input,array());
		}

		public function trending_news_watchlist($input)
		{
			$this->set_path('public/trending-news-watchlist');
			return $this->post($input,array());
		}

		public function trending_news_statistics($input)
		{
			$this->set_path('public/trending-news-statistics');
			return $this->post($input,array());
		}


	}

