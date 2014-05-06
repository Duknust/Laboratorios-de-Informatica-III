/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.util;

import java.util.*;

/**
 *
 * @author duarteduarte
 */
public class Factories {
    
    public static <K,V> Map<K,V> giveMeMap(){
        return new TreeMap<K,V> ();
    }
    
    public static <V> Set<V> giveMeSet(){
        return new TreeSet<V>();
    }
    
    public static <T> List<T> giveMeList(){
        return new LinkedList<T>();
    }
    
    public static <T> List<T> giveMeList(Collection<T> ts){
        List<T> res = null;
        if(ts != null)
            res=new LinkedList<T>(ts);
        else 
            res=new LinkedList<T>();
        
        return res;
    }
}
