separate funcs in files based on solid
remember readme file

# semaphore
ipcs -s

// Remove a specific shared memory segment identified by <semid>.
ipcrm -s <semid>

# memory
// Display all shared memory segments.
ipcs -m

// Remove a specific shared memory segment identified by <shmid>.
ipcrm -m <shmid>

// Remove all shared memory segments by iterating over the IDs obtained from the ipcs -m command.
for id in $(ipcs -m | awk 'NR>3 {print $2}'); do ipcrm -m $id; done


## admin
su root
# pwd: admin

## path
cd Documents/Lab3_2024
cd Documents/Lab3_2024/parciales/rec1

## Process
top (list top processes)
kill [pId]