plasmoid.setPreferredSize(24, 800)
label = new Label();
label.wordWrap = false;

function recv(job, data)
{
    if (job == getJob) {
        if (data.length) {
            label.text = data.toUtf8();
        }
    }
}

function fini(job)
{
    timer.start(100)
}

function refresh() {
    getJob = plasmoid.getUrl("file:///tmp/xmonadstate")
    getJob.data.connect(recv);
    getJob.finished.connect(fini);
}

var timer = QTimer();
timer.timeout.connect(refresh)

layout = new LinearLayout(plasmoid);
layout.addItem(label);
timer.start(100)
