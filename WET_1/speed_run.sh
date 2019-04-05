TIMEFORMAT=%R
if [ "$#" -ne 2 ]; then
   echo "Usage: ./speed_run.sh <your_exec_file> speed_test.in"
   exit -1
fi
if [ ! -f speed_exe ]; then
    echo "speed_exe not found!"
    exit -1
fi
if [ ! -f $1 ]; then
    echo "exec file not found!"
    exit -1
fi
if [ ! -f $2 ]; then
    echo "test input file not found!"
    exit -1
fi
naive_time=$(time ( ./speed_exe < $2 > /dev/null ) 2>&1 1>/dev/null)
echo "Naive implementation time: $naive_time"
student_time=$(time ( ./$1 < $2 > /dev/null ) 2>&1 1>/dev/null)
echo "Your time: $student_time"
speedup=`bc <<< "scale=4; $naive_time/$student_time"`
echo "Speedup is: $speedup"
