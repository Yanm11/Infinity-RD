package il.co.ilrd.WaitablePQ.src;

import java.util.Comparator;

public class Movie implements Comparable<Movie>{
    private String name;
    private int year;
    private int rating;

    public Movie(String name, int year, int rating){
        this.name = name;
        this.year = year;
        this.rating = rating;
    }

    public int getRating() {
        return rating;
    }

    public int getYear() {
        return year;
    }

    public String getName() {
        return name;
    }

    @Override
    public int compareTo(Movie movie) {
        return year - movie.year;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o){ return true; }
        if(o == null) { return false; }
        if(!(o instanceof Movie)) { return false; }
        return this.getName().equals(((Movie)o).getName());
    }
}

class CompareByRating implements Comparator<Movie>{
    @Override
    public int compare(Movie movie, Movie t1) {
        return movie.getRating() - t1.getRating();
    }
}

