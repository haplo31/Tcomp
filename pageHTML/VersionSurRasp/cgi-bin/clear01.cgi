#!/bin/bash

gpio -p write 200 0
gpio -p write 201 0
echo "Status: 204 No Content"
echo "Content-type: text/plain"
echo ""
