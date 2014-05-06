/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.processing;

/**
 *
 * @author duarteduarte
 */
import org.duarteduarte.li3.data.Autor;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.duarteduarte.li3.util.Factories;

public class FileHandling implements Serializable {

    private FileHandling() {
    }

    public static int writeToFile(Map<Integer, List<Autor>> autores) throws FileNotFoundException, IOException {
        FileOutputStream fos = new FileOutputStream("/Users/duarteduarte/Desktop/java_dblp/out.obj");
        ObjectOutputStream oos = new ObjectOutputStream(fos);

        oos.writeObject(autores);

        return 0;
    }

    public static Map<Integer, List<Autor>> readFromFile() throws FileNotFoundException, IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream("/Users/duarteduarte/Desktop/java_dblp/out.obj");
        ObjectInputStream ois = new ObjectInputStream(fis);

        return (Map<Integer, List<Autor>>) ois.readObject();
    }

    public static List<String> leLinhasScanner(String fichName) {

        List<String> linhas = Factories.giveMeList();
        Scanner fichScan = null;
        try {
            fichScan = new Scanner(new FileReader(fichName));
            fichScan.useDelimiter(System.getProperty("line.separator"));
            while (fichScan.hasNext()) {
                linhas.add(fichScan.next());
            }
            fichScan.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
            return null;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

        return linhas;
    }

    public Storage load() {
        Storage store = null;
        FileInputStream fis;
        ObjectInputStream ois;

        try {
            fis = new FileInputStream("redeautores.dd");
            ois = new ObjectInputStream(fis);
            store = (Storage) ois.readObject();
            ois.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(FileHandling.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FileHandling.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(FileHandling.class.getName()).log(Level.SEVERE, null, ex);
        }
        return store;
    }

    public void save(Storage store) {
        FileOutputStream fos;
        ObjectOutputStream oos;

        try {
            fos = new FileOutputStream("redeautores.dd");
            oos = new ObjectOutputStream(fos);
            oos.writeObject(store);
            oos.flush();
            oos.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Storage.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Storage.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
