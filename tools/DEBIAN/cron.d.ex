#
# Regular cron jobs for the kbe package
#
0 4	* * *	root	[ -x /opt/kbe/kbe ] && /opt/kbe/kbe
