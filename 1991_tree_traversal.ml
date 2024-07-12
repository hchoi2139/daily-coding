type 'a tree =
  | Leaf
  | Node of 'a node

and 'a node =
  { value : 'a
  ; lt : 'a tree
  ; rt : 'a tree
  }

let read_triple () = Scanf.scanf "%c %c %c\n" (fun a b c -> a, b, c)
let idx_of_alpha c = Char.code c - Char.code 'A'

let build_tree lst =
  let nodes = Array.make 26 None in
  List.iter
    (fun (value, lt, rt) ->
      let idx = idx_of_alpha value in
      nodes.(idx) <- Some (value, lt, rt))
    lst;
  let rec build_tree_from_idx idx =
    match nodes.(idx) with
    | None -> failwith "unreachable region"
    | Some (value, lt, rt) ->
      let lt_tr = if lt = '.' then Leaf else build_tree_from_idx (idx_of_alpha lt) in
      let rt_tr = if rt = '.' then Leaf else build_tree_from_idx (idx_of_alpha rt) in
      Node { value; lt = lt_tr; rt = rt_tr }
  in
  build_tree_from_idx @@ idx_of_alpha 'A'
;;

let preorder tree =
  let rec pre_aux acc = function
    | Leaf -> acc
    | Node { value; lt; rt } -> value :: pre_aux (pre_aux acc rt) lt
  in
  pre_aux [] tree
;;

let inorder tree =
  let rec in_aux acc = function
    | Leaf -> acc
    | Node { value; lt; rt } ->
      let acc_rt = in_aux acc rt in
      let acc_lt = in_aux (value :: acc_rt) lt in
      acc_lt
  in
  in_aux [] tree
;;

let postorder tree =
  let rec post_aux acc = function
    | Leaf -> acc
    | Node { value; lt; rt } -> post_aux (post_aux (value :: acc) rt) lt
  in
  post_aux [] tree
;;

let print_char_lst_ln lst =
  List.iter (Printf.printf "%c") lst;
  Printf.printf "\n"
;;

let () =
  let num_nodes = read_int () in
  let input =
    let rec read_lines n acc =
      if n = 0 then List.rev acc else read_lines (n - 1) (read_triple () :: acc)
    in
    read_lines num_nodes []
  in
  let tree = build_tree input in
  let preord = preorder tree in
  print_char_lst_ln preord;
  let inord = inorder tree in
  print_char_lst_ln inord;
  let postord = postorder tree in
  print_char_lst_ln postord
;;
