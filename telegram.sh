#!/bin/bash

TIME="5"
TELEGRAM_BOT_TOKEN=5551635265:AAEiMbo0_7Rw8MIIuczC-ZdQ-lVHSA7-Oe0
TELEGRAM_USER_ID=782145002
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
if ! [ "$1" -eq "FAIL" ]; then
    curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
    curl -F document=@"3.webm"  https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendDocument?chat_id="$TELEGRAM_USER_ID" > /dev/null
else
    curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
    curl -F document=@"1.webm"  https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendDocument?chat_id="$TELEGRAM_USER_ID" > /dev/null
fi
