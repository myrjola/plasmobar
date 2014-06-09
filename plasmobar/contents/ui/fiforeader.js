label = new Label();

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
    timer.start(333)
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
