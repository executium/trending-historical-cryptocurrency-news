# Installation for Python Cryptocurrency Trending News
The following `readme` is intended to provide direction about how you use the related files to access executium's trending news service. This python source code will work from `Python 2.7.17` and above.

#### Direction

* Make sure you have [python](https://www.python.org/downloads/) installed.

* Open a command line interface then use the package manager [pip](https://pip.pypa.io/en/stable/) to install both pycurl and certifi.

    ```bash
    pip install pycurl certifi
    ```

* Both examples and src folders must be under the same directory. The directory structure should look like this
    ```
    .
    ├── examples
    │   ├── __init__.py
    │   ├── config.py
    │   └── script.py
    ├── src
    │   ├── __init__.py
    │   └── Class.py
    └── README.md
    ```

#### Usage
To run the package you need to open a command line interface under the directory containing the examples.

```bash
cd /path/to/project/folder/examples
```

Then run the following command

```bash
python [script-name].py
```

#### Output

Example output:

```json
{
    "data": 
    [
        {
            "price_impact_1800s": {
                "status": "Subscription required.",
                "data": []
            },
            "domain": "cryptonews.com",
            "tone": {
                "status": "Subscription required.",
                "data": []
            },
            "title": "More South Korean Banks May Look to Start Crypto Operations",
            "url": "https://cryptonews.com/news/more-south-korean-banks-may-look-to-start-crypto-operations-7017.htm",
            "price_impact_3600s": {
                "status": "completed",
                "data": {
                    "adausdt": {
                        "status": "compiled",
                        "pair": "ADAUSDT",
                        "difference": "0.00246000",
                        "after": "0.09894000",
                        "before": "0.09648000"
                    },
                    "ethbtc": {
                        "status": "compiled",
                        "pair": "ETHBTC",
                        "difference": "0.00000200",
                        "after": "0.02485600",
                        "before": "0.02485400"
                    },
                    "xrpusdt": {
                        "status": "compiled",
                        "pair": "XRPUSDT",
                        "difference": "0.00045000",
                        "after": "0.17710000",
                        "before": "0.17665000"
                    },
                    "ethusdt": {
                        "status": "compiled",
                        "pair": "ETHUSDT",
                        "difference": "0.22000000",
                        "after": "225.40000000",
                        "before": "225.18000000"
                    },
                    "adabtc": {
                        "status": "compiled",
                        "pair": "ADABTC",
                        "difference": "0.00000026",
                        "after": "0.00001091",
                        "before": "0.00001065"
                    },
                    "xrpbtc": {
                        "status": "compiled",
                        "pair": "XRPBTC",
                        "difference": "0.00000002",
                        "after": "0.00001952",
                        "before": "0.00001950"
                    },
                    "btcusdt": {
                        "status": "compiled",
                        "pair": "BTCUSDT",
                        "difference": "7.50000000",
                        "after": "9067.98000000",
                        "before": "9060.48000000"
                    }
                }
            },
            "image": "https://cimg.co/w/articles/2/5ef/f57c9d47bb.jpg",
            "author": "Tim Alper",
            "brief": "More South Korean conventional finance firms are set to follow Nonghyup (NH Bank) into the cryptocurrency industry, say experts, academics and industry ...",
            "keywords": "currency,crypto,cryptocurrency",
            "price_impact_900s": {
                "status": "Subscription required.",
                "data": []
            },
            "source": "Cryptonews",
            "price_impact_120s": {
                "status": "Subscription required.",
                "data": []
            },
            "date": {
                "format2": "4th July 2020 00:22",
                "day": "Saturday",
                "time_published": "1593822145",
                "format1": "2020-07-04"
            },
            "price_impact_600s": {
                "status": "Subscription required.",
                "data": []
            },
            "price_impact_300s": {
                "status": "Subscription required.",
                "data": []
            },
            "id": "779682",
            "price_impact_1200s": {
                "status": "Subscription required.",
                "data": []
            }
        }, 
    ],
    "meta": {
        "api_version": 2,
        "reqid": "83579G3195DT1593876258",
        "system_version": "2.0.5",
        "endpoint": "public/trending-news-data",
        "status": 200,
        "timezone": "UTC",
        "request": "api/v2/public/trending-news-data",
        "auth_success": true,
        "rateLimits": {
            "minute": 60
        },
        "subscription": {
            "id": "0",
            "name": "Free"
        },
        "auth_required": true,
        "ms": 1593876258982,
        "time": 1593876258,
        "process_time": 0.034865,
        "process_full": 0.034865,
        "requester": <YOUR-IP>
    }
}
```

#### Authentication keys
For the parts which do not require a `subscription` you do not need to add a `key` or `secret`. These can be obtained via executium.com if required.
