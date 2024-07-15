type vertex = int
type weight = int
type neighbor = vertex * weight

module VertexSet = Set.Make (struct
    type t = weight * vertex

    let compare = Stdlib.compare
  end)

let read_pii () = Scanf.scanf "%d %d\n" (fun a b -> a, b)
let read_tiii () = Scanf.scanf "%d %d %d\n" (fun a b c -> a, b, c)

let dijkstra (src : vertex) (adj_list : neighbor list array) : weight array * vertex array
  =
  let n = Array.length adj_list in
  let min_dist = Array.make n Int.max_int in
  min_dist.(src) <- 0;
  let prev = Array.make n (-1) in
  let rec aux vertex_queue =
    if not (VertexSet.is_empty vertex_queue)
    then (
      let dist, u = VertexSet.min_elt vertex_queue in
      let vertex_queue' = VertexSet.remove (dist, u) vertex_queue in
      let neighbors = adj_list.(u) in
      let f vertex_queue (v, weight) =
        let dist_thru_u = dist + weight in
        if dist_thru_u >= min_dist.(v)
        then vertex_queue
        else (
          let vertex_queue' = VertexSet.remove (min_dist.(v), v) vertex_queue in
          min_dist.(v) <- dist_thru_u;
          prev.(v) <- u;
          VertexSet.add (min_dist.(v), v) vertex_queue')
      in
      aux @@ List.fold_left f vertex_queue' neighbors)
  in
  aux @@ VertexSet.singleton (min_dist.(src), src);
  min_dist, prev
;;

let shortest_path_to (target : vertex) (prev : vertex array) : int * vertex list =
  let rec aux target len_acc acc =
    if target == -1 then len_acc, acc else aux prev.(target) (len_acc + 1) (target :: acc)
  in
  aux target 0 []
;;

let () =
  let n = read_int () in
  let m = read_int () in
  let adj_list =
    let rec read_lines (m : int) (adj_list : neighbor list array) : neighbor list array =
      if m = 0
      then adj_list
      else (
        let from_city, to_city, cost = read_tiii () in
        adj_list.(from_city) <- (to_city, cost) :: adj_list.(from_city);
        read_lines (m - 1) adj_list)
    in
    let adj_list = Array.make (n + 1) [] in
    read_lines m adj_list
  in
  let src, dest = read_pii () in
  let min_dist, prev = dijkstra src adj_list in
  Printf.printf "%d\n" min_dist.(dest);
  let len_path, path = shortest_path_to dest prev in
  Printf.printf "%d\n" len_path;
  List.iter (Printf.printf "%d ") path
;;
