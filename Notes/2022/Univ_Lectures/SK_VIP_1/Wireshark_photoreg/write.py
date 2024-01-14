import influxdb_client
from influxdb_client.client.write_api import SYNCHRONOUS

bucket = "test"
org = "pin"
token = ""
# Store the URL of your InfluxDB instance
url = "http://localhost:8086"

client = influxdb_client.InfluxDBClient(
    url=url,
    token=token,
    org=org
)

# Write script
write_api = client.write_api(write_options=SYNCHRONOUS)

#p = influxdb_client.Point("m2").tag("location", "Prague").field("temperature", 25.3)
p = influxdb_client.Point("m4").tag("t1", "v1").tag("t2", "v2").field("f1", 10)
write_api.write(bucket=bucket, org=org, record=p)
