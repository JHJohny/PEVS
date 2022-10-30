import java.text.SimpleDateFormat;
import java.util.*;
import java.util.Date;
import java.util.PriorityQueue;

interface Task {
    public void TakeOverTheTask(); //The task is now being handled by user
    public void SolveTheTask();
}

class FIKTIVTask implements Task {
    private String Description;
    private Date creationDate;
    private boolean prioritized;

    public FIKTIVTask (String _description, Date _creationDate, boolean _prioritized) {
        setDescription(_description);
        setCreationDate(_creationDate);
        setPrioritized(_prioritized);
    }

    public void TakeOverTheTask () {
        // TODO
    }

    public void SolveTheTask () {
        // TODO
    }

    // ### Getters and setters ### //
    public boolean isPrioritized() {
        return prioritized;
    }

    public void setPrioritized(boolean prioritized) {
        this.prioritized = prioritized;
    }

    public Date getCreationDate() {
        return creationDate;
    }

    public void setCreationDate(Date creationDate) {
        this.creationDate = creationDate;
    }

    public String getDescription() {
        return Description;
    }

    public void setDescription(String description) {
        Description = description;
    }
}

class AdministrationTask extends FIKTIVTask{

    private int daysPostponed;

    public AdministrationTask(String _string) {
        super(_string);
    }

    public void PostponeTask () {
        daysPostponed += 1;
    }

    @Override
    public Date getCreationDate() {
        System.out.println("Subclass");
        return super.getCreationDate(); //TODO do summary
    }
}

class ComplaintTask extends FIKTIVTask{

    public ComplaintTask(String _string) {
        super(_string);
    }

    public void CancelTask () {

    }
}


public class Main {
    public static void main(String[] args)
    {

    }
}