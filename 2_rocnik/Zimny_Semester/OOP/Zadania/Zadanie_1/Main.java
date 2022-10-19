import java.io.File;
import java.nio.file.Paths;

enum filterType {
    VOICE, INTERNET, UZERNIK, MOBILE //Uzernik stands for someone who doesn't pay bills - therefore we send an uzernik at him
}

class CLIParser {
    private String fileName;
    private filterType filterType;

    public CLIParser (String _argOne, String _argTwo) throws Exception {
        if (!isFileNameOK(_argOne) || !isFilterOK(_argTwo)) {
            throw new Exception("Arguments are not OK!");
        }
    }

    private boolean isFileNameOK (String _fileName) {

        //Checking if filename is more than just suffix => '.csv'
        if (_fileName.length() <= 4) {
            return false;
        }

        //Checking if filename is .csv file
        if (! (_fileName.endsWith(".csv"))) {
            return false;
        }

        File file = new File("./" + _fileName);
        //Checking if filename is file and not directory
        if (file.isDirectory()) {
            System.out.println("Filename is a directory, not file! " + file.getName());
            return false;
        }

        //Checking if the file exists
        if (!file.exists()) {
            System.out.println("Subor neexistuje, prosim vytvor alebo presun subor do adresara projektu!");
            return false;
        }

        //All checks went trought - therefore filename is OK
        setFileName(_fileName);
        return true;
    }

    private boolean isFilterOK (String _filterType) {

        //Checking if it's really just a single letter
        if (_filterType.length() != 1) {
            return false;
        }

        //Checking the actual filterType whether it's OK
        switch (_filterType) {
            case "h":
                setFilterType(filterType.VOICE);
                return true;
            case "i":
                setFilterType(filterType.INTERNET);
                return true;
            case "f":
                setFilterType(filterType.UZERNIK);
                return true;
            case "m":
                setFilterType(filterType.MOBILE);
                return true;
            default:
                return false;
        }
    }

    //Getters and setters
    public void setFileName(String _fileName) {
        fileName = _fileName;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFilterType(filterType _filterType) {
        filterType = _filterType;
    }

    public filterType getFilterType() { return filterType; }
}

public class Main {
    public static void main(String[] args) throws Exception {
        try {
            CLIParser cliParser = new CLIParser(args[0], args[1]);
        }catch (Exception ex){
            throw new Exception("Arguments are not OK!");
        }

        System.out.println("Yay it went trough");
    }
}