## Node SDK for Cryptocurrency Trending News
This is the Node JS SDK for development of the trending news script. Too use the free version of the application you do not need an API `key` or `secret`. 

### Simple example :
```javascript
const ApiAccess = require('./ApiAccess');

const client = new ApiAccess('', '');

client.post('public/trending-news-data', { date: '2020-07-06' }, {})
    .then((res) => {
      console.log(res);
    })
    .catch((err) => {
      console.log(err);
    });
```
**Example output of `console.log(res);`**

```javascript
{
  success: true,
  returned: {
    data: [
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object], [Object], [Object],
      [Object], [Object], [Object], [Object],
      ... 684 more items
    ],
    meta: {
      api_version: 2,
      reqid: '45608G46957T1594087394',
      system_version: false,
      endpoint: 'public/trending-news-data',
      status: 200,
      timezone: 'UTC',
      request: 'api/v2/public/trending-news-data',
      auth_required: false,
      ms: 1594087394115,
      time: 1594087394,
      process_time: 0.03491,
      process_full: 0.035709,
      requester: '<YOUR-IP>'
    }
  }
}
```

**Example output of the news data if using console.log(res.returned.data);**
```javascript
 {
    id: '1081747',
    date: {
      time_published: '1594008600',
      day: 'Monday',
      format1: '2020-07-06',
      format2: '6th July 2020 04:10'
    },
    title: 'Global Blockchain Market Expected to reach highest CAGR by 2025: IBM (US), AWS (US), Microsoft (US), SAP (Germany), Intel (US)',
    brief: 'This report on Global Blockchain Market is based on the in-depth view of Blockchain industry on the basis of market growth, market size, development plans and ...',
    keywords: 'blockchain',
    url: 'https://primefeed.in/news/289478/global-blockchain-market-expected-to-reach-highest-cagr-by-2025-ibm-us-aws-us-microsoft-us-sap-germany-intel-us/',
    source: 'Owned',
    image: '',
    domain: 'primefeed.in',
    author: '',
    price_impact_120s: { status: 'Subscription required.', data: [] },
    price_impact_300s: { status: 'Subscription required.', data: [] },
    price_impact_600s: { status: 'Subscription required.', data: [] },
    price_impact_900s: { status: 'Subscription required.', data: [] },
    price_impact_1200s: { status: 'Subscription required.', data: [] },
    price_impact_1800s: { status: 'Subscription required.', data: [] },
    price_impact_3600s: { status: 'completed', data: [Object] },
    tone: { status: 'Subscription required.', data: [] }
  },
  ... 684 more items
```


### More involved example:
```javascript
const ApiAccess = require('./ApiAccess');

const client = new ApiAccess('', '', {
  timeout: 1000,
  domain: 'https://trendingnews.executium.com',
  version: 2,
  userAgent: 'Trending News Node v2'
});

client.loadEndpoints()
  .then((endpoints) => {
    console.log(client.endpoints, endpoints);
  })
  .catch((err) => {
    console.log(err);
  });

client.post('public/trending-news-sources', { }, {})
    .then((res) => {
      console.log(res);
    })
    .catch((err) => {
      console.log(err);
    });
    
```
