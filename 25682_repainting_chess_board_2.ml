(** [from i j l] is the list containing the integers from [i] to [j],
    inclusive, followed by the list [l].
    Example:  [from 1 3 [0] = [1; 2; 3; 0]] *)
let rec from i j l = if i > j then l else from i (j - 1) (j :: l)

(** [i -- j] is the list containing the integers from [i] to [j], inclusive. *)
let ( -- ) i j = from i j []

(** [is_coloured_properly i j e] is true if the (i, j)-th position of the
    square chess board whose top-leftmost corner is coloured in black. *)
let is_coloured_properly i j e = if (i + j) mod 2 = 0 then e = 'B' else e = 'W'

let () =
  let n, m, k =
    let input = read_line () in
    Scanf.sscanf input "%d %d %d" (fun x y z -> x, y, z)
  in
  let squares_in_chess_board = k * k in
  let p_sum = Array.make_matrix (n + 1) (m + 1) 0 in
  List.iter
    (fun i ->
      String.iteri
        (fun j e ->
          let j = j + 1 in
          p_sum.(i).(j) <- p_sum.(i - 1).(j) + p_sum.(i).(j - 1) - p_sum.(i - 1).(j - 1);
          if is_coloured_properly i j e then () else p_sum.(i).(j) <- p_sum.(i).(j) + 1)
        (read_line ()))
    (1 -- n);
  (* [br_xs] is the index of x coordinates of the bottom-rightmost corner of
     possible k * k boards. Similar for [br_ys]. *)
  let br_xs, br_ys = k -- n, k -- m in
  let res =
    List.fold_left
      (fun acc i ->
        List.fold_left
          (fun acc' j ->
            Stdlib.min acc'
            @@
            let squares_to_repaint =
              p_sum.(i).(j)
              - p_sum.(i).(j - k)
              - p_sum.(i - k).(j)
              + p_sum.(i - k).(j - k)
            in
            Stdlib.min squares_to_repaint (squares_in_chess_board - squares_to_repaint))
          acc
          br_ys)
      Int.max_int
      br_xs
  in
  Printf.printf "%d\n" res
;;
