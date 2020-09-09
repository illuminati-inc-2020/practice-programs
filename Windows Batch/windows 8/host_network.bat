::netsh wlan set hostednetwork mode=allow ssid=Rakesh
netsh wlan set hostednetwork mode=allow ssid=Rakesh key="12345678"
netsh wlan start hostednetwork
if %errorlevel%==1 pause