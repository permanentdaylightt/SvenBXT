#!/bin/sh
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

# If your Steam library is somewhere else, correct this path.
export SVEN_ROOT="."

# SvenBXT path (you can correct this path too)
export SVENBXT="$SVEN_ROOT/libSvenBXT.so"

# Check that the Sven Co-op folder exists.
if [ ! -d "$SVEN_ROOT" ]; then
    echo "Sven Co-op folder does not exist at $SVEN_ROOT"
    exit 1
fi

# Check that SvenBXT exists.
if [ ! -f "$SVENBXT" ]; then
    echo "SvenBXT does not exist at $SVENBXT"
    exit 1
fi

export LD_PRELOAD="$LD_PRELOAD:$SVENBXT"

# Run Sven Co-op.
export LD_LIBRARY_PATH="$SVEN_ROOT:$LD_LIBRARY_PATH"
export SteamEnv=1

cd "$SVEN_ROOT" || exit 1
exec ./svencoop_linux -steam "$@"