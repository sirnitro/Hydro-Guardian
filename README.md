# Hydro Guardian

Run grabData.php from cron on whatever interval you want to use to upload fresh data.

Adding hydroGrab.service

Move the file to the proper directory

mv hydroGrab.service /etc/systemd/system/.

enable to service

systemctl enable hydroGrab
