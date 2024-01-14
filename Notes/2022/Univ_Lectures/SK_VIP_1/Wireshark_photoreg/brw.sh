#! /bin/bash

echo "==== sending REST API request : POST ===="
echo "bucket : $1";
echo "measurement : $2";
echo "srcip : $3";
echo "dstip : $4";
echo "srcport : $5";
echo "dstport : $6";
echo "data : $7";

curl --request POST "http://localhost:8086/api/v2/write?org=pin&bucket=$1&precision=ns" --header "Authorization: Token " --header "Content-Type: text/plain; charset=utf-8" --header "Accept: application/json" --data-binary "$2,srcip=$3,dstip=$4,srcport=$5,dstport=$6 light=$7"

echo "==== end of request ===="