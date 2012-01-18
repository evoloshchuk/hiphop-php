#!/bin/bash -e

set -e

SCRIPT_DIR="$(dirname "${BASH_SOURCE[0]}")"

function wrong_args {
	echo "Usage: $(basename "$0") [OPTION]... BASE_SOURCE_DIR..."
	echo "Options:"
	echo "  -i SED_COMMAND_FILE"
	echo "  -c CONFIG_FILE"
	echo "  -v INLINE_OPTION"
	echo "  -o OUT_DIR"
	echo "  -p PROGRAM_NAME"
	echo "  -C CLUSTERS"
	echo "  -j JOBS"
	exit 1
}

SED_CMD_FILES=()
OPTIONS=()
OUT_DIR="hiphop-out"
CLUSTERS=0
JOBS=1
PROGRAM_NAME="program"
while getopts "i:c:v:o:p:C:j:" OPTION; do
	case $OPTION in
		i)
			SED_CMD_FILES[${#SED_CMD_FILES[@]}]="$OPTARG"
			;;
		c|v)
			OPTIONS[${#OPTIONS[@]}]="-$OPTION"
			OPTIONS[${#OPTIONS[@]}]="$OPTARG"
			;;
		o)
			OUT_DIR="$OPTARG"
			;;
		p)
			PROGRAM_NAME="$OPTARG"
			;;
		C)
			CLUSTERS="$OPTARG"
			;;
		j)
			JOBS="$OPTARG"
			;;
		?)
			wrong_args
			;;
	esac
done
shift $(($OPTIND - 1))
if [ $# -lt 1 ]; then
	echo "No source directory specified"
	wrong_args
fi
COMPILE_LIST="$OUT_DIR/compile.lst"

echo -n "Setting up... "
. "$SCRIPT_DIR/setup.sh"
if [ -d "$OUT_DIR" ]; then
	echo "ERROR: output directory \"$OUT_DIR\" already exists"
	exit 1
fi

mkdir "$OUT_DIR"
cp "$HPHP_LIB/CMakeLists.base.txt" "$OUT_DIR/CMakeLists.txt"

TIMEFORMAT="DONE (%3lR)"
echo "DONE"

echo -n "Generating source file list... "
time find $@ -name "*.php" -o -name "*.inc" > "$COMPILE_LIST"
for SED_CMD_FILE in "${SED_CMD_FILES[@]}"; do
	sed -i -f "$SED_CMD_FILE" "$COMPILE_LIST"
done
echo "Found $(wc -l "$COMPILE_LIST" | cut -d' ' -f1) source files"

"$HPHP_HOME/src/hphp/hphp" -t cpp -o "$OUT_DIR" -l 3 \
	--force 1 --parse-on-demand 0 \
	--cluster-count "$CLUSTERS" \
	--input-list "$COMPILE_LIST" \
	--program "$PROGRAM_NAME" \
	--opts "deadcode,localcopy,string,cflow" \
	"${OPTIONS[@]}"

cd "$OUT_DIR"

echo "Checking for distcc support"
if [ -e "/etc/distcc/hosts" ]; then
	echo "Compiling with distcc"

	echo "Run cmake..."
	TIMEFORMAT="cmake took %3lR (%3lU user, %3lS system)"
	time DISTCC_FALLBACK=0 HOSTCC='distcc gcc' CC='distcc gcc' CXX='distcc g++' \
		cmake -D "PROGRAM_NAME:string=$PROGRAM_NAME" .

	echo "Run make..."
	TIMEFORMAT="make took %3lR (%3lU user, %3lS system)"
	time DISTCC_FALLBACK=0 make -j "$JOBS" \
		HOSTCC='distcc gcc' CC='distcc gcc' CXX='distcc g++' "$PROGRAM_NAME/fast"
else
	echo "You have no distcc support, (/etc/distcc/hosts not found)"

	echo "Run cmake..."
	TIMEFORMAT="cmake took %3lR (%3lU user, %3lS system)"
	time cmake -D "PROGRAM_NAME:string=$PROGRAM_NAME" .

	echo "Run make..."
	TIMEFORMAT="make took %3lR (%3lU user, %3lS system)"
	time make -j "$JOBS" "$PROGRAM_NAME/fast"
fi
