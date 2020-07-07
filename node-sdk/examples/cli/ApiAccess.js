const https = require('https');
const http = require('http');
const assert = require('assert');
const crypto = require('crypto');
const querystring = require('querystring');

module.exports = class ApiAccess {
  endpoints = [];

  constructor(apiKey, apiSecret, options = {}) {
    assert.ok(typeof apiKey === 'string', 'apiKey must be a string');
    assert.ok(typeof apiSecret === 'string', 'apiSecret must be a string');
    assert.ok(
      Object.prototype.toString.call(options) === '[object Object]',
      'options must be an object'
    );

    this._apiKey = apiKey;
    this._apiSecret = apiSecret;
    this._options = {
      ...{
        userAgent: 'API v2 (node cli)',
        version: 2,
        domain: 'https://trendingnews.executium.com',
        timeout: 3000,
      },
      ...options,
    };
  }

  nonce() {
    return Math.round(Date.now() * 10000);
  }

  getApiUrl(path) {
    assert.ok(typeof path === 'string');
    return `${this._options.domain}/api/v${this._options.version}/${path}`;
  }

  async loadEndpoints(input = {}) {
    try {
      const res = await this.post('system/ep', input, {});
      this.endpoints = res.returned.data;
      return this.endpoints;
    } catch (e) {
      throw new Error('Failed to load endpoints');
    }
  }

  auth(payload) {
    assert.ok(
      Object.prototype.toString.call(payload) === '[object Object]',
      'payload must be an object'
    );

    const b01 = this.sanitize(
      Buffer.from('{"typ":"JWT","alg":"HS256"}').toString('base64')
    );

    const b02 = this.sanitize(
      Buffer.from(JSON.stringify({ ...payload, nonce: this.nonce() })).toString(
        'base64'
      )
    );

    const b03 = this.sanitize(
      crypto
        .createHmac('sha256', this._apiSecret)
        .update(`${b01}.${b02}`)
        .digest('base64')
    );

    return `${b01}.${b02}.${b03}`;
  }

  send(path, input, payload) {
    return this.post(path, input, payload);
  }

  post(path, input, payload) {
    assert.ok(typeof path === 'string', 'path must be a string');
    assert.ok(
      Object.prototype.toString.call(input) === '[object Object]',
      'input must be an object'
    );
    assert.ok(
      Object.prototype.toString.call(payload) === '[object Object]',
      'payload must be an object'
    );

    return new Promise((resolve, reject) => {
      const data = querystring.stringify(input);

      const options = {
        method: data.length ? 'POST' : 'GET',
        headers: {
          key: this._apiKey,
          authorization: this.auth(payload),
          'User-Agent': this._options.userAgent,
          ...(data.length
            ? {
                'Content-Type': 'application/x-www-form-urlencoded',
                'Content-Length': Buffer.byteLength(data),
              }
            : {}),
        },
        timeout: this._options.timeout,
      };

      const req = (this.isSecure() ? https : http).request(
        this.getApiUrl(path),
        options,
        (res) => {
          const chunks = [];

          res.on('data', (chunk) => {
            chunks.push(chunk);
          });

          res.on('end', () => {
            const returned = chunks.length
              ? this.decode(Buffer.concat(chunks).toString('utf8'))
              : {};

            !Object.keys(returned).length || returned.meta.status !== 200
              ? reject({
                  success: false,
                  returned,
                })
              : resolve({
                  success: true,
                  returned,
                });
          });
        }
      );

      req.on('error', () => {
        reject({
          success: false,
          returned: {},
        });
      });

      if (Object.keys(input).length) {
        req.write(data);
      }

      req.end();
    });
  }

  isSecure() {
    return this._options.domain.startsWith('https://');
  }

  sanitize(base64) {
    assert.ok(typeof base64 === 'string', 'base64 must be a string');

    return base64.replace(/=|\/|\+/g, (match) => {
      switch (match) {
        case '+':
          return '-';
        case '/':
          return '_';
        case '=':
          return '';
        default:
          return match;
      }
    });
  }

  decode(result) {
    assert.ok(typeof result === 'string', 'result must be a string');

    try {
      return JSON.parse(result);
    } catch (e) {
      console.log('Failed to parse JSON');
      return {};
    }
  }
};
