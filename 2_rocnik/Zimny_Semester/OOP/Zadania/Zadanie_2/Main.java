import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.Date;
import java.util.PriorityQueue;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
        //System.out.println("Subclass");
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
    private TaskParser parser = new TaskParser();

    public FIKTIVsroSoftware (String _filePath) throws Exception {
        ConsumeTheFile(_filePath);
    }

    public void LoadNewFile (String _filePath) throws Exception {
        ConsumeTheFile(_filePath);
    }

    private void ConsumeTheFile (String _filePath) throws Exception {
        if (!FileUtils.DoesFileExist(_filePath)) {
            throw new Exception("File cannot be found!");
        }

        try (BufferedReader br = new BufferedReader(new FileReader(_filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                queue.add(parser.getTaskFromLine(line));
            }
        }
    }

}

class TaskParser {
    private enum TaskTypes { administrative, complaint}
    private Properties properties = new Properties();
    public <T extends FIKTIVTask> T getTaskFromLine (String _line) throws Exception {
        System.out.println("This is the line " + _line);

        String[] lineValues = _line.split(",");

        System.out.println("This is the task type " + getTaskType(lineValues[0]));

        switch (getTaskType(lineValues[0])) {
            case complaint:
                return (T) new ComplaintTask("", new Date(), false);
            case administrative:
                return (T) new AdministrationTask("", new Date(), false);
            default:
                throw new Exception("The task could not be recognized");
        }
    }

    private TaskTypes getTaskType (String _string) throws Exception {
        Config config = Config.getConfig();
        String[] ADMINISTRATIVE_TASK_REGEXES = config.properties.getProperty("ADMINISTRATIVE_TASK_REGEXES").split(",");
        String[] COMPLAINT_TASK_REGEXES = config.properties.getProperty("COMPLAINT_TASK_REGEXES").split(",");

        for (String administrative_task_regex : ADMINISTRATIVE_TASK_REGEXES) {
            Pattern pattern = Pattern.compile(administrative_task_regex, Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(_string);

            if (matcher.find()) {
                return TaskTypes.administrative;
            }
        }

        for (String administrative_task_regex : COMPLAINT_TASK_REGEXES) {
            Pattern pattern = Pattern.compile(administrative_task_regex, Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(_string);

            if (matcher.find()) {
                return TaskTypes.complaint;
            }
        }

        throw new Exception("Task could not be found!");
    }
}

class FileUtils {
    static boolean DoesFileExist(String _filePath) {
        File file = new File(_filePath);
        return file.exists() && !file.isDirectory();
    }
}

class Config {
    private static Config config_instance = null;

    Properties properties = new Properties();

    private Config () throws IOException {
        properties.load(Config.class.getResourceAsStream("config.ini"));
    }

    public static Config getConfig() throws IOException {
        if (config_instance == null)
            config_instance = new Config();

        return config_instance;
    }
}

public class Main {
    public static void main(String[] args) throws Exception {

        FIKTIVsroSoftware FIKTIV = new FIKTIVsroSoftware("test.csv");
    }
}