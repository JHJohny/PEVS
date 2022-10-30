import java.io.File;
import java.util.*;
import java.util.Date;
import java.util.PriorityQueue;

interface Task {
    public void TakeOverTheTask(); //The task is now being handled by user
    public void SolveTheTask();
    public Date getCreationDate();
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

interface AdministrationTaskInterface {
    public void PostponeTask();
}

class AdministrationTask extends FIKTIVTask implements AdministrationTaskInterface {

    private int daysPostponed;

    public AdministrationTask(String _description, Date _creationDate, boolean _prioritized) {
        super(_description, _creationDate, _prioritized);
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

interface ComplaintTaskInterface {
    public void CancelTask();
}

class ComplaintTask extends FIKTIVTask implements ComplaintTaskInterface{

    public ComplaintTask(String _description, Date _creationDate, boolean _prioritized) {
        super(_description, _creationDate, _prioritized);
    }

    public void CancelTask () {

    }
}

class TaskComparator implements Comparator<Task>{
    @Override
    public int compare(Task task1, Task task2) {
        if (task1.getCreationDate().before(task2.getCreationDate()))
            return 1;
        else if (task1.getCreationDate().after(task2.getCreationDate()))
            return -1;
        return 0;
    }
}

class FIKTIVsroSoftware {

    private PriorityQueue<Task> queue = new PriorityQueue<Task>(new TaskComparator());

    public FIKTIVsroSoftware (String _filePath) throws Exception {
        if (!FileUtils.DoesFileExist(_filePath)) {
            throw new Exception("File cannot be found!");
        }

        // TODO - do the rest

    }

    public void LoadNewFile (String _filePath) throws Exception {
        if (!FileUtils.DoesFileExist(_filePath)) {
            throw new Exception("File cannot be found!");
        }

        // TODO - load file
    }
}

class FileUtils {
    static boolean DoesFileExist(String _filePath) {
        File file = new File(_filePath);
        return file.exists() && !file.isDirectory();
    }
}

public class Main {
    public static void main(String[] args)
    {

    }
}