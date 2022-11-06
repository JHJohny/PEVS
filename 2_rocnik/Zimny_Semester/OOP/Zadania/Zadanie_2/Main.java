import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.security.cert.TrustAnchor;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.Date;
import java.util.PriorityQueue;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

interface Task {
    public void TakeOverTheTask(); //The task is now being handled by user
    public void SolveTheTask();
    public Date getCreationDate();
    public boolean isPrioritized();
}

class FIKTIVTask implements Task, Comparable<FIKTIVTask> {
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

    @Override
    public int compareTo(FIKTIVTask o) {
        return getCreationDate().compareTo(o.getCreationDate());
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
        //Todo update prioritized
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

        int result = task2.getCreationDate().compareTo(task1.getCreationDate());
        return result;

    }
}

class FIKTIVsroSoftware {

    private PriorityQueue<Task> queue = new PriorityQueue<Task>(new TaskComparator());
    private List myList = new ArrayList();
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
                //Task myTask = parser.getTaskFromLine(line);
                //queue.add(parser.getTaskFromLine(line));
                myList.add(parser.getTaskFromLine(line));
            }

            myList.size();
            Collections.sort(myList);
            myList.size();
            //queue.size();
        }
    }

}

class TaskParser {
    private enum TaskTypes { administrative, complaint}
    private Properties properties = new Properties();
    private Config config;
    public TaskParser () throws IOException {
        config = Config.getConfig();
    }
    public <T extends FIKTIVTask> T getTaskFromLine (String _line) throws Exception {
        String[] lineValues = _line.split(",", -1);

        switch (getTaskType(lineValues[0])) {
            case complaint:
                return (T) new ComplaintTask(lineValues[1], getDate(lineValues[2]), IsTaskPrioritized(lineValues[3]));
            case administrative:
                return (T) new AdministrationTask(lineValues[1], getDate(lineValues[2]), IsTaskPrioritized(lineValues[3]));
            default:
                throw new Exception("The task could not be recognized");
        }
    }

    private TaskTypes getTaskType (String _string) throws Exception {
        String[] ADMINISTRATIVE_TASK_REGEXES = config.properties.getProperty("ADMINISTRATIVE_TASK_REGEXES").split(",");
        String[] COMPLAINT_TASK_REGEXES = config.properties.getProperty("COMPLAINT_TASK_REGEXES").split(",");

        if (RegexUtils.FindMatch(ADMINISTRATIVE_TASK_REGEXES, _string) != null)
            return TaskTypes.administrative;
        if (RegexUtils.FindMatch(COMPLAINT_TASK_REGEXES, _string) != null)
            return TaskTypes.complaint;
        throw new Exception("Task could not be found!");
    }

    private Date getDate (String _string) throws Exception {
        String[] DATE_FORMAT_LINUX_REGEX = config.properties.getProperty("DATE_FORMAT_LINUX_REGEX").split(",");
        String[] DATE_FORMATS = config.properties.getProperty("DATE_FORMATS").split(",");

        Date date = null;

        date = DateUtils.FindDate(DATE_FORMATS, _string);

        if (RegexUtils.FindMatch(DATE_FORMAT_LINUX_REGEX, _string) != null)
            date = new Date(Long.parseLong(_string) * 1000L);

        if (date == null)
            throw new Exception("Date could not be found! Is it possible, that file was damaged meanwhile?");

        return date;
    }

    private boolean IsTaskPrioritized (String _string) throws Exception {
        String[] POSITIVE_PRIORITY_REGEXES = config.properties.getProperty("POSITIVE_PRIORITY_REGEXES").split(",");
        String[] NEGATIVE_PRIORITY_REGEXES = config.properties.getProperty("NEGATIVE_PRIORITY_REGEXES").split(",");

        // In case - no string was left after the split
        if (Objects.equals(_string, "") || _string == null)
            return false;

        if (RegexUtils.FindMatch(POSITIVE_PRIORITY_REGEXES, _string) != null)
            return true;
        if (RegexUtils.FindMatch(NEGATIVE_PRIORITY_REGEXES, _string) != null)
            return false;

        throw new Exception("The priority could not be recognized from the line!");
    }

}

class FileUtils {
    static boolean DoesFileExist(String _filePath) {
        File file = new File(_filePath);
        return file.exists() && !file.isDirectory();
    }
}

class RegexUtils {
    static String FindMatch (String[] patterns, String _string) {
        for (String _pattern : patterns) {
            Pattern pattern = Pattern.compile(_pattern, Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(_string);

            if (matcher.find()) {
                return matcher.group();
            }
        }

        return null;
    }
}

class DateUtils {
    static Date FindDate (String[] _dateFormats, String _string) {
        Date date = null;
        for (String dateFormat : _dateFormats) {
            try {
                date = new SimpleDateFormat(dateFormat).parse(_string);
            } catch (Exception ex) {}
        }

        return date;
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