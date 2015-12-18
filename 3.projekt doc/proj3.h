/**
 * @file   proj3.h
 * @author Filip Kolesár (xkoles06@stud.fit.vutbr.cz)
 * @date   12/2015
 * @brief  Documentation of analysis
 */

/**
 * @addtogroup Sctructures
 * @{
 */

/**
 * @brief    Structure of object
 * 
 * @param 	id 	Identification number
 * @param 	x 	Axis X
 * @param 	y 	Axis Y
 */
struct obj_t {
    int id;
    float x;
    float y;
};

/**
 * @brief    Structure of cluster
 * 
 * @param 	size 		Current size of cluster
 * @param 	capacity 	Current capacity of cluster
 * @param 	obj 		Pointer at the first object in cluster
 */
struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};
/** @} */

/**
 * @addtogroup Cluster_functions
 * @{
 */

/**
 * @brief    Cluster initialization
 * 
 * @param 	c 		pointer to structure
 * @param 	cap 	capacity
 * 
 * @pre      'c' doesn't point to NULL
 * @pre      capacity is not of negative value
 * 
 * @post     Memory for cluster allocated, else empty cluster
 */
void init_cluster(struct cluster_t *c, int cap);

/**
 * @brief    Deletes objects and init to an empty cluster
 * 
 * @param 	c 	Cluster address
 * 
 * @post     Clean cluster
 */
void clear_cluster(struct cluster_t *c);

/// Chunk of cluster objects. Value recommended for reallocation.
extern const int CLUSTER_CHUNK;

/**
 * @brief    Resizes cluster to a new capacity
 * 
 * @param 		c 			Cluster address
 * @param[in] 	new_cap 	Value of new capacity
 * 
 * @pre      Pointer 'c' is not pointing to NULL
 * @pre      Cluster capacity is not negative
 * @pre      Value of new capacity is not negative
 * 
 * @return   Pointer to modified cluster, otherwise NULL at return
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * @brief    Appends given object to the end of cluster
 * 
 * @param 		c 		Cluster address
 * @param[in] 	obj 	Object given to be apended
 * 
 * @post     If success: object apended to the end of cluster, else: nothing happened
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * @brief    Appends all objects from cluster2 to cluster1
 * @details  Appending all objects from cluster2 given as 2nd parameter of function to cluster1 (1st parameter)
 * 	If there is not enough capacity in cluster1, cluster1 is resized.
 * 
 * @param 	c1 	Destination, where will be added objects
 * @param 	c2 	Source of objects for copying
 * 
 * @pre      Addresses of both clusters are not pointing to NULL
 * 
 * @post     Cluster1 is sorted, Cluster2 stays untouched
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * @brief    Removes cluster from array of clusters
 * @details  This function removes cluster with ID given as last parameter (idx) from array of clusters.
 * 
 * @param 		carr 	Pointer to first cluster in an array of clusters
 * @param[in] 	narr 	Number of clusters in an array of clusters
 * @param[in] 	idx 	Index of cluster being deleted
 * 
 * @return   New number of clusters in clusters array
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);
/** @} */

/**
 * @addtogroup Object_functions
 * @{
 */

 /**
 * @brief    Calculates Euclidean distance between two objects
 * 
 * @param[in] 	o1 	Pointer to object
 * @param[in] 	o2 	Pointer to object
 * 
 * @pre      Clusters are not empty
 * 
 * @return   Distance
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * @brief    Calculates distance between given clusters
 * @details  Finding closest objects of two clusters.

 * @param[in] 	o1 	Pointer to object
 * @param[in] 	o2 	Pointer to object
 * 
 * @pre      Clusters are not empty
 * 
 * @return   Distance is based on closest objects.
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * @brief    Finds the nearest neighbours in an array of clusters
 * 
 * @param 		carr 	Pointer to the first cluster of an array of clusters
 * @param[in] 	narr 	Size of an array of clusters
 * @param[out] 	c1 		Pointer to cluster given as param
 * @param[out] 	c2 		Pointer to cluster given as param
 * 
 * @pre      Array of clusters contains at least one cluster
 * 
 * @post     Pointers c1 and c2 are pointing to the nearest clusters in an array of clusters
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/**
 * @brief    Sorts objects in the cluster by ID
 * 
 * @param 	c 	Pointer to clusters
 * 
 * @post     Objects in cluster are sorted by ID
 */
void sort_cluster(struct cluster_t *c);

/**
 * @brief    Prints cluster to stdout
 * 
 * @param 	c 	Pointer to cluster being printed
 */
void print_cluster(struct cluster_t *c);

/**
 * @brief    Loads Objects
 * @details  Loads the objects from the file and creating new cluster to each. Although allocating memory for them
 * 
 * @param[in] 	filename 	String containing name of file
 * @param 		arr 		Pointer to the first pointer in array of pointers
 * 
 * @return   Amount of objects loaded
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
 * @brief    Prints clusters to stdout
 * 
 * @param 		carr 	Pointer to an array of clusters
 * @param[in] 	narr 	Amount of clusters in an array of clusters
 */
void print_clusters(struct cluster_t *carr, int narr);
/** @} */;