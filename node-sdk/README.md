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
### More involved example :
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
