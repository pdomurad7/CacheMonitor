if (cmake --build /root/CacheMonitor/build --config Debug --target all -j 10 --)
then
    ./build/cache_monitor
fi