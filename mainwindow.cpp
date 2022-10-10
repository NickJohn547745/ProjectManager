#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GitHubModel *model = new GitHubModel("a03f73c9d240585dbef3");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*curl \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer <YOUR-TOKEN>" \
  https://api.github.com/repos/OWNER/REPO/projects

SOURCE_PROJECT_ID=<TO_FILL>
TARGET_PROJECT_ID=<TO_FILL>

sourceColumnIds=( $(curl \
  -H "Authorization: token ${GITHUB_AUTH_TOKEN}" \
  -H "Accept: application/vnd.github.inertia-preview+json" \
  https://api.github.com/projects/${SOURCE_PROJECT_ID}/columns | jq .[].id) )

targetColumnIds=( $(curl \
  -H "Authorization: token ${GITHUB_AUTH_TOKEN}" \
  -H "Accept: application/vnd.github.inertia-preview+json" \
  https://api.github.com/projects/${TARGET_PROJECT_ID}/columns | jq .[].id) )

echo "Source project column ids:"; printf '%s\n' "${sourceColumnIds[@]}"
echo "Target project column ids:"; printf '%s\n' "${targetColumnIds[@]}"

if [ "${#videos[@]}" -ne "${#subtitles[@]}" ]; then
    echo "Different number of columns in between projects"
    exit -1
fi

for sourceColumnIndex in "${!sourceColumnIds[@]}"
do
    sourceColumnId=${sourceColumnIds[$sourceColumnIndex]}
    sourceColumnId=${sourceColumnId//[^a-zA-Z0-9_]/}
    targetColumnId=${targetColumnIds[$sourceColumnIndex]}
    targetColumnId=${targetColumnId//[^a-zA-Z0-9_]/}
    curl \
      -H "Authorization: token ${GITHUB_AUTH_TOKEN}" \
      -H "Accept: application/vnd.github.inertia-preview+json" \
      https://api.github.com/projects/columns/${sourceColumnId}/cards \
      | jq reverse \
      | jq -c '.[]' \
      | while read card; do
        note=$(jq '.note' <<< "$card")
        data='{"note":'${note}'}'
        curl \
          -w 'HTTP Status: %{http_code}' --silent --output /dev/null \
          -X POST \
          -H "Authorization: token ${GITHUB_AUTH_TOKEN}" \
          -H "Accept: application/vnd.github.inertia-preview+json" \
          -d "${data}" \
          https://api.github.com/projects/columns/${targetColumnId}/cards
        echo " for card migration: ${note}"
    done
done*/
