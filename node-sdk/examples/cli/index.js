#!/usr/bin/env node
const ApiAccess = require('./ApiAccess');

require('yargs')
  .coerce({
    input: JSON.parse,
    payload: JSON.parse,
  })
  .command(
    'request <path> [input] [payload]',
    'request command',
    (yargs) => {
      yargs
        .positional('path', {
          type: 'string',
          describe: 'path to request',
        })
        .positional('input', {
          type: 'string',
          default: '{}',
          describe: 'input of the request',
        })
        .positional('payload', {
          type: 'string',
          default: '{}',
          describe: 'payload of the request',
        });
    },
    async (argv) => {
      const client = new ApiAccess(argv.apiKey, argv.apiSecret);

      try {
        console.log(await client.post(argv.path, argv.input, argv.payload));
      } catch (e) {
        console.error('Request failed');
        console.error(e);
      }
    }
  )
  .option('apiKey', {
    alias: 'key',
    type: 'string',
    description: 'API Key',
  })
  .option('apiSecret', {
    alias: 'secret',
    type: 'string',
    description: 'API Secret',
  })
  .demandOption(['apiKey', 'apiSecret'])
  .demandCommand()
  .argv;
