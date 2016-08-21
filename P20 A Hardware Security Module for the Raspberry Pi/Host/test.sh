#! /bin/bash
prog=/mnt/NFS/root/rpi/P20/Host/HSM_Host
failed=0
i=0
while sleep 1; do
	echo Encode.
	"$prog" "Password, $i" < "$*" > "$*.enc"
	echo Decode.
	"$prog" "Password, $i" < "$*.enc" > "$*.dec"
	echo Diff.
	diff "$*" "$*.dec"
	echo -e "Done: $((++i)), failed: $((failed += ($? != 0))).\n"
	rm "$*.enc" "$*.dec"
done
exit
