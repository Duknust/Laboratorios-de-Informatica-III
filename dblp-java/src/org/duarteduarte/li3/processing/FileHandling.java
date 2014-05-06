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
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.*;
import org.duarteduarte.li3.util.Factories;

public class FileHandling {
    
    private FileHandling(){}

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
}
