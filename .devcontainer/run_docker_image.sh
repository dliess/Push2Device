#!/bin/bash

function print_usage
{
	echo "usage: $0 <repo dir>"
}

if [[ $# != 1 ]]
then
	print_usage
	exit 1
fi

REPO_DIR=$(readlink -f $1)

AUDIO_GROUP_ID=$(getent group audio | awk -F: '{printf $3}')

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
source "$DIR/common.sh"

docker run --privileged \
         --expose 50051 \
			--group-add $AUDIO_GROUP_ID \
        	--mount type=bind,source=$REPO_DIR,target=/home/$BUILD_USER/repos \
       	-ti $DOCKER_IMAGE_TAG:latest /bin/bash

## logging in to a running container:
## get id with: docker ps
## docker exec -it <id> /bin/bash
