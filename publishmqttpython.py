import paho.mqtt.client as mqttClient
import time
import requests
import json
from geopy.distance import vincenty

'''def geolocation():
	g=geocoder.ip('me')
	lat,lon=g.latlng
	lat2,lon2= radians(20.985),radians( 80.3697)
	R= 6373.0
	lat1=radians(lat)
	lon1=radians(lon)

	dlon=lon2-lon1
	dlat=lat2-lat1

	a=sin(dlat/2)**2+cos(lat1)*cos(lat2)*sin(dlon/2)**2
	c=2*atan2(sqrt(a),sqrt(1-a))

	geocoderdistance=R*c
	return distance,lat,lon
	#print (distance)

	#print (lat,lon)
'''
def geoloc():
        send_url = "http://api.ipstack.com/check?access_key=7b531d5c14f239eda4bd5168cadc2beb"
        geo_req = requests.get(send_url)
        geo_json = json.loads(geo_req.text)
        latitude = geo_json['latitude']
        longitude = geo_json['longitude']
        coords_1=(latitude,longitude)
        coords_2=(lat2,lon2)= (22.572646,88.363895)
        city = geo_json['city']
        distance= vincenty(coords_1, coords_2).km
        print (latitude,longitude,city)
        return distance,latitude,longitude



def on_connect(client, userdata, flags, rc):
 
    if rc == 0:
 
        print("Connected to broker")
 
        global Connected                #Use global variable
        Connected = True                #Signal connection 
 
    else:
 
        print("Connection failed")
 
Connected = False   #global variable for the state of the connection
 
broker_address= "iot.iandwe.in"
port = 1883
##user = "hello"
##password = "shantam1234"
 
client = mqttClient.Client("Python")               #create new instance
##client.username_pw_set(user, password=password)    #set username and password
client.on_connect= on_connect                      #attach function to callback
client.connect(broker_address, port=port)          #connect to broker
 
client.loop_start()        #start the loop
 
while Connected != True:    #Wait for connection
    time.sleep(1)
 
try:
    while True:
 
        #value = input('Enter the message:')
        distance,lat,lon=geoloc()
        client.publish("Anything/SIT",str(distance))
        time.sleep(5)
 
except KeyboardInterrupt:
 
    client.disconnect()
    client.loop_stop()
