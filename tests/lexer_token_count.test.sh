#!/bin/sh

[ $(halk 'tests/lexer_token_count.test.halk' | grep -c "token type") -eq 8 ] && echo "$0 pass" || echo "$0 fail"
