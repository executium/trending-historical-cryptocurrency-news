const express = require('express');
const ApiAccess = require('./ApiAccess');

const client = new ApiAccess(
  process.env.API_KEY || '',
  process.env.API_SECRET || ''
);

const app = express();

app.get('/', async (req, res) => {
  try
  {
    res.json(
      await client.post
      (
        req.query.path,
        JSON.parse(req.query.input || '{}'),
        JSON.parse(req.query.payload || '{}')
      )
    );
  } catch (e) {
    res.json(e);
  }
});

app.listen(3000);
