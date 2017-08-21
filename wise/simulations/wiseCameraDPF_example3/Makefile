LOG_FILE	:= dpf_results.txt
LOG_PART_FILE	:= dpf_part_results.txt

all:
	Castalia -c General

clean:
	find . -maxdepth 1 -regex "./[0-9]+-[0-9]+.*" | xargs rm -rf
	rm -rf Castalia-Trace.txt
	rm -rf $(LOG_FILE) $(LOG_PART_FILE)
