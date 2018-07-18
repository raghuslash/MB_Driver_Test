last="0"
found="1"
while true
do
	x=$(curl https://dweet.io/get/latest/dweet/for/RBC-meeting-ac)
	now=$(echo ${x} | jq '.with[].created')
	# echo "now: $now"
	if [ "$now" = "$last" ];then
		echo "Latest command was:  $found"
	else
		echo ${x} | jq '.with[].content.cmd'
		found=$(echo ${x} | jq '.with[].content.cmd')
		echo "New command found: $found"
		last="$now"
		# echo "last: $last"
		echo "Publishing new command to MQTT..."
		mosquitto_pub -t 'actuate/modbus/ac' -m $found
	fi
done
