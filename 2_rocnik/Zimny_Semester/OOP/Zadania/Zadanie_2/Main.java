import java.util.Date;

interface Task {
    public void TakeOverTheTask(); //The task is now being handled by user
    public void SolveTheTask();
}

class FIKTIVTask implements Task {
    public enum taskTypes { administration, complaint };

    private taskTypes taskType;
    private String Description;
    private Date creationDate;
    private int daysPostponed;
    private boolean prioritized;

    public FIKTIVTask (String _string) {
        // TODO
    }

    public void TakeOverTheTask () {
        // TODO
    }

    public void SolveTheTask () {
        // TODO
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
    }
}