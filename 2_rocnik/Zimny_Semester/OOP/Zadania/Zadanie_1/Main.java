import java.io.File;
import java.nio.file.Paths;
import java.util.AbstractList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;

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

class ZakaznikovUdaj {

    private String customerName;
    private String contactNumber;
    private boolean voiceServicePurchased;
    private boolean internetServicePurchased;
    private int balance;

    enum paymentTypes {kredit, pausal}
    private paymentTypes paymentType;
    enum phoneTypes {mobile, fixedLine}
    private phoneTypes phoneType;

    public ZakaznikovUdaj (String _line) {
        String[] records = _line.split(",");

        customerName = records[0];
        contactNumber = records[1];

        if (contactNumber.charAt(1) == '2') {
            phoneType = phoneTypes.fixedLine;
        } else {
            phoneType = phoneTypes.mobile;
        }

        voiceServicePurchased = !Objects.equals(records[2], "");
        internetServicePurchased = !Objects.equals(records[3], "");

        if (Objects.equals(records[4], "kredit")) {
            paymentType = paymentTypes.kredit;
        } else {
            paymentType = paymentTypes.pausal;
        }

        balance = Integer.parseInt(records[5]);
    }

    public boolean hasCustomerVoiceServicePurchased () { return voiceServicePurchased; }
    public boolean hasCustomerInternetServicePurchased () { return internetServicePurchased; }
    public int getCustomerBalance () { return balance; }
    public phoneTypes getCustomerPhoneType () { return phoneType; }

    public void printFormatedRecord () {
        System.out.println("" + customerName + "\t\t" + contactNumber + "\t" + balance);
    }
}

class ZakaznickyZoznam {

    private File file;
    private ZakaznikovUdaj[] zakaznici;
    public ZakaznickyZoznam (String _file) throws Exception {
        file = new File(_file);
        Scanner reader;
        int count = 0;

        //Handling if the file is already opened somewhere
        if (!file.canRead()) { throw new Exception("Subor nie je momentalne citatelny! Prosim uzatvor ho v druhom programe"); }

        //Counting the lines
        reader = new Scanner(file);
        while (reader.hasNextLine()) {
            String line = reader.nextLine();
            count++;
        }
        zakaznici = new ZakaznikovUdaj[count];
        count = 0;

        //Getting the actual records
        reader = new Scanner(file);
        while (reader.hasNextLine()) {
            String line = reader.nextLine();
            ZakaznikovUdaj udaj = new ZakaznikovUdaj(line);

            zakaznici[count] = udaj;

            count++;
        }
    }

    public void printZakazniciFormatted (filterType _filterType) {

        switch (_filterType) {
            case INTERNET:
                for (ZakaznikovUdaj zakaznikovUdaj : zakaznici) {
                    if (zakaznikovUdaj.hasCustomerInternetServicePurchased()) {
                        zakaznikovUdaj.printFormatedRecord();
                    }
                }
                break;
            case MOBILE:
                for (ZakaznikovUdaj zakaznikovUdaj : zakaznici) {
                    if (zakaznikovUdaj.getCustomerPhoneType() == ZakaznikovUdaj.phoneTypes.mobile) {
                        zakaznikovUdaj.printFormatedRecord();
                    }
                }
                break;
            case UZERNIK:
                for (ZakaznikovUdaj zakaznikovUdaj : zakaznici) {
                    if (zakaznikovUdaj.getCustomerBalance() < 0) {
                        zakaznikovUdaj.printFormatedRecord();
                    }
                }
                break;
            case VOICE:
                for (ZakaznikovUdaj zakaznikovUdaj : zakaznici) {
                    if (zakaznikovUdaj.hasCustomerVoiceServicePurchased()) {
                        zakaznikovUdaj.printFormatedRecord();
                    }
                }
                break;
        }

    }
}

public class Main {
    public static void main(String[] args) throws Exception {
        CLIParser cliParser = new CLIParser(args[0], args[1]);
        ZakaznickyZoznam customerList = new ZakaznickyZoznam(cliParser.getFileName());

        customerList.printZakazniciFormatted(cliParser.getFilterType());
    }
}