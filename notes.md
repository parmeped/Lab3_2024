separate funcs in files based on solid
remember readme file

-- memory
ipcs -m
ipcrm -m <shmid>

for id in $(ipcs -m | awk '{print $2}'); do ipcrm -m $id; done
for id in $(ipcs -m | awk 'NR>3 {print $2}'); do ipcrm -m $id; done
-