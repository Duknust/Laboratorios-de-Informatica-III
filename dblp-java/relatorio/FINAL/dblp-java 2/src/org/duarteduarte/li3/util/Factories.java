/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.util;

import java.io.Serializable;
import java.util.*;

/**
 *
 * @author duarteduarte
 */
public class Factories implements Serializable{

    public static <K, V> Map<K, V> giveMeMap() {
        return new TreeMap<K, V>();
    }

    public static <V> Set<V> giveMeSet() {
        return new TreeSet<V>();
    }
 
    public static <T> List<T> giveMeList() {
        return new LinkedList<T>();
    }
    
    public static <V> Set<V> giveMeSet(Collection<V> vs) {
        return new TreeSet<V>(vs);
    }


    public static <T> List<T> giveMeList(Collection<T> ts) {
        List<T> res = null;
        if (ts != null) {
            res = new LinkedList<T>(ts);
        } else {
            res = new LinkedList<T>();
        }

        return res;
    }
}
